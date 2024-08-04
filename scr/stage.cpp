#include "stage.h"
extern App app;

Stage stage;
int highscore;
Entity *player;
SDL_Texture *enemyTexture, *background;
int enemySpawnTimer = 0, stageResetTimer;

/*Khởi tạo người chơi, bao gồm việc cấp phát bộ nhớ,
 thiết lập vị trí ban đầu, và tải texture cho người chơi.*/
static void initPlayer()
{
    player = (Entity *)malloc(sizeof(Entity));
    if (!player) 
    {
        fprintf(stderr, "Failed to allocate memory for player\n");
        exit(1);
    }
    memset(player, 0, sizeof(Entity));
    stage.enemyTail->next = player;
    stage.enemyTail = player;

    player->x = rand() % (SCREEN_WIDTH-100);
    player->y = 100;
    
    player->texture = loadTexture("data\\images\\jhin01.jpg");
    if (!player->texture) 
    {
        fprintf(stderr, "Failed to load player texture: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

    //player->side = SIDE_PLAYER;
}


/*Khoảng cách cố định giữa các kẻ thù*/
static const int ENEMY_SPAWN_GAP = 100;

/*Sinh ra kẻ thù mới tại các vị trí ngẫu nhiên trên màn hình 
sau một khoảng thời gian nhất định.*/
static void spawnEnemies(void)
{
    Entity *enemy;

    if (--enemySpawnTimer <= 0) 
    {
        enemy = (Entity *)malloc(sizeof(Entity));
        if (!enemy) 
        {
            fprintf(stderr, "Failed to allocate memory for enemy\n");
            exit(1);
        }
        memset(enemy, 0, sizeof(Entity));
        stage.enemyTail->next = enemy;
        stage.enemyTail = enemy;

        enemy->x = rand() % (SCREEN_WIDTH-100);

        // Đặt vị trí y của kẻ thù ở cuối màn hình
        enemy->y = SCREEN_HEIGHT ; 
       
        enemy->texture = enemyTexture;
        enemy->dy = BOARD_SPEED; // Tốc độ di chuyển cố định của kẻ thù gốc

        // Đặt thời gian sinh kẻ thù mới dựa trên khoảng cách cố định và tốc độ di chuyển
        enemySpawnTimer = ENEMY_SPAWN_GAP / abs(enemy->dy); 
        enemy->reload = FPS * (1 + (rand() % 3));
        //enemy->side = SIDE_BOARD;
    }
}

/*Xử lý logic di chuyển của người chơi dựa trên đầu vào từ bàn phím. 
cập nhật vị trí của người chơi dựa trên tốc độ di chuyển.*/
static void doPlayer(void)
{
    if(player != NULL)
    {
    player->dx = player->dy = 0;

    if (player->reload > 0) 
    {
        player->reload--;
    }

    /*if (app.keyboard[SDL_SCANCODE_UP] && player->y >= 0 ) 
    {
        player->dy = -PLAYER_SPEED;
    }*/

    if (app.keyboard[SDL_SCANCODE_DOWN] && player->y <= SCREEN_HEIGHT-PLAYER_HEIGHT) 
    {
        player->dy = PLAYER_SPEED;
        stage.score++;
        playSound(SND_PLAYER_MOVE, CH_PLAYER);
    }

    if (app.keyboard[SDL_SCANCODE_LEFT] && player->x >= 0) 
    {
        player->dx = -PLAYER_SPEED;
        stage.score++;
        playSound(SND_PLAYER_MOVE, CH_PLAYER);
    }

    if (app.keyboard[SDL_SCANCODE_RIGHT] && player->x <= SCREEN_WIDTH-PLAYER_WIDTH) 
    {
        player->dx = PLAYER_SPEED;
        stage.score++;
        playSound(SND_PLAYER_MOVE, CH_PLAYER);
    }

    /*Đặt trọng lực*/
    player->gravitySpeed += GRAVITY;
    if (player->gravitySpeed > MAX_FALL_SPEED) 
    {
        player->gravitySpeed = MAX_FALL_SPEED;
    }
    player->y += player->gravitySpeed;

    /* Kiểm tra va chạm với kẻ thù */
    for (Entity* enemy = stage.enemyHead.next; enemy != NULL; enemy = enemy->next) 
    {
        handleCollisions(player, enemy);
        //stage.score++;
        //if(stage.score > highscore) highscore=stage.score;
    }
    //highscore=std::max(highscore, stage.score);
    /* Kiểm tra xem người chơi có ra khỏi màn hình không */
    if (IsPlayer(player)) 
    {
    highscore = std::max(highscore, stage.score);
    playSound(SND_PLAYER_DIE, CH_PLAYER);

    // Ghi điểm cao vào tệp
    std::string base_path = std::string(SDL_GetBasePath()); 
    //std::ofstream file((base_path + "data/highscore.txt").c_str());
    
    // Đọc tất cả điểm số từ tệp
    std::vector<int> scores;
    std::ifstream scoreFile((base_path + "data/highscore.txt").c_str());
    int score;
    while (scoreFile >> score)
    {
        scores.push_back(score);
    }
    scoreFile.close();

    if(std::size(scores)==8)
    {
        if(stage.score > scores.back())
        {
            scores.back() = stage.score;
        }
    }
    else if(std::size(scores) < 8)
    {
        scores.push_back(stage.score);
    }

    // Sắp xếp danh sách điểm số
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    // Ghi lại danh sách điểm số vào tệp
    std::ofstream updatedFile((base_path + "data/highscore.txt").c_str());
    if (updatedFile.is_open())
    {
    for (int updatedScore : scores)
    {
        updatedFile << updatedScore << "\n";
    }
    updatedFile.close();
    }

    else
    {
        exit(0);
    }

    SDL_Delay(500);
    initHighscores();
    }
    }

}

/*Xử lý logic di chuyển cho tất cả các thực thể chiến đấu (bao gồm cả người chơi và kẻ thù). 
 xóa các thực thể ra khỏi màn hình.*/
static void doEnemies(void)
{
    Entity *e, *prev;

    prev = &stage.enemyHead;

    for (e = stage.enemyHead.next; e != NULL; e = e->next) 
    {
        e->x += e->dx;
        e->y += e->dy;

        if (e != player && e->x < -e->w) 
        {
            if (e == stage.enemyTail) 
            {
                stage.enemyTail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }

        prev = e;
    }
}

static void resetStage(void)
{
    Entity *e;

    while (stage.enemyHead.next)
    {
        e = stage.enemyHead.next;
        stage.enemyHead.next = e->next;
        free(e);
    }


    memset(&stage, 0, sizeof(Stage));
    stage.enemyTail = &stage.enemyHead;
    //stage.bulletTail = &stage.bulletHead;

    initPlayer();

    enemySpawnTimer = 0;

    stageResetTimer = FPS * 2;

    stage.score = 0;

}

/* Khai báo biến backgroundX và gán giá trị mặc định là 0*/
static int backgroundX = 0;

static void doBackground(void)
{
    if (--backgroundX < -SCREEN_WIDTH)
    {
        backgroundX = 0;
    }
}

/*Gọi các hàm xử lý logic*/
static void logic(void)
{
    //doBackground();
    doPlayer();

    doEnemies();
    
    spawnEnemies();

    if (player == NULL && --stageResetTimer <= 0)
    {
        resetStage();
    }


    if (player == NULL && --stageResetTimer <= 0)
    {
        addHighscore(stage.score);

        initHighscores();
    }
}

/*Vẽ người chơi lên màn hình.*/
static void drawPlayer(void)
{
    blit_player(player->texture, player->x, player->y);
}

/*Vẽ kẻ thù lên màn hình*/
static void drawEnemies(void)
{
    Entity *e;

    for (e = stage.enemyHead.next; e != NULL; e = e->next) 
    {
        if (e != player) 
        {
            blit_board(e->texture, e->x, e->y);
        }
    }
}

/*Vẽ ảnh nền*/ 
static void drawBackground(void)
{
    SDL_Rect dest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(app.renderer, background, NULL, &dest);
    /*SDL_Rect dest;
    int x;

    for (x = backgroundX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH)
    {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;

        SDL_RenderCopy(app.renderer, background, NULL, &dest);
    }*/
}
/*Vẽ chữ lên màn hình*/
static void drawHud(void)
{

    drawText_score(0, 50, "SCORE: ", stage.score);
    std::string base_path = std::string(SDL_GetBasePath()); 
    std::ifstream scoreFile((base_path + "data/highscore.txt").c_str());
    if(scoreFile.is_open())
    {
        scoreFile >> highscore;
        scoreFile.close();
    }
    drawText_highscore(0, 0, "HIGH SCORE:  ",highscore);
  
    //if(stage.score>highscore)
}


/*Gọi các hàm vẽ để vẽ người chơi và kẻ thù lên màn hình, sau đó cập nhật renderer.*/
static void draw(void)
{

    drawBackground();

    drawPlayer();

    drawEnemies();

    drawHud();

    SDL_RenderPresent(app.renderer); // cập nhật renderer
}

/*Giới hạn tốc độ khung hình để đảm bảo trò chơi chạy mượt mà và không quá nhanh.*/
void capFrameRate(long *then)
{
    const int targetFrameTime = 16; // 16 ms for 60 FPS (adjust as needed)

    long frameTime = SDL_GetTicks() - *then;
    if (frameTime < targetFrameTime)
    {
        SDL_Delay(targetFrameTime - frameTime);
    }

    *then = SDL_GetTicks();
}



void initStage(void)
{
    
    
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(Stage));
    stage.enemyTail = &stage.enemyHead;
    //stage.boardTail = &stage.boardHead;
    //stage.heartTail = &stage.heartHead;
    initPlayer();

    /*Khai báo tệp chứa hình kẻ thù*/
    enemyTexture = loadTexture("data\\images\\hmm.jpg");

    /*Khai báo tệp chứa ảnh nền*/
    background = loadTexture("data\\images\\00.jpg");
    
    if (!enemyTexture)
     {
        fprintf(stderr, "Failed to load enemy texture: %s\n", SDL_GetError());
        exit(1);
    }

}
