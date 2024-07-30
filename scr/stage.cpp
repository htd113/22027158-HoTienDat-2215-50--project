#include "stage.h"
extern App app;

Stage stage;

Entity *player, *heart;
SDL_Texture *enemyTexture, *heartTexture, *background;
int enemySpawnTimer = 0, heartSpawnTimer = 0;

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
    
    player->texture = loadTexture("data\\images\\monster.jpg");
    if (!player->texture) 
    {
        fprintf(stderr, "Failed to load player texture: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

    //player->side = SIDE_PLAYER;
}

/*static void initHeart()
{
    heart = (Entity *)malloc(sizeof(Entity));
    if (!heart) 
    {
        fprintf(stderr, "Failed to allocate memory for player\n");
        exit(1);
    }
    memset(heart, 0, sizeof(Entity));
    stage.enemyTail->next = heart;
    stage.enemyTail = heart;

    heart->x = rand() % (SCREEN_WIDTH-100);
    heart->y = rand() % SCREEN_HEIGHT;
    
    heart->texture = loadTexture("data\\images\\tim.jpg");
    if (!heart->texture) 
    {
        fprintf(stderr, "Failed to load player texture: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_QueryTexture(heart->texture, NULL, NULL, &heart->w, &heart->h);

    //player->side = SIDE_PLAYER;
}
*/

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

        //enemy->side = SIDE_BOARD;
    }
}

/*Xử lý logic di chuyển của người chơi dựa trên đầu vào từ bàn phím. 
cập nhật vị trí của người chơi dựa trên tốc độ di chuyển.*/
static void doPlayer(void)
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
        //playSound(SND_PLAYER_MOVE, CH_PLAYER);
    }

    if (app.keyboard[SDL_SCANCODE_LEFT] && player->x >= 0) 
    {
        player->dx = -PLAYER_SPEED;
        //playSound(SND_PLAYER_MOVE, CH_PLAYER);
    }

    if (app.keyboard[SDL_SCANCODE_RIGHT] && player->x <= SCREEN_WIDTH-PLAYER_WIDTH) 
    {
        player->dx = PLAYER_SPEED;
        //playSound(SND_PLAYER_MOVE, CH_PLAYER);
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
    }

    /* Kiểm tra xem người chơi có ra khỏi màn hình không */
    if (  player->y < 0 || player->y > SCREEN_HEIGHT) 
    {
        // Xử lý tùy ý (ví dụ: kết thúc trò chơi)
        //playSound(SND_PLAYER_DIE, CH_PLAYER);
        exit(0); // Thoát chương trình
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

static void doHearts(void)
{
     // Cập nhật thời gian tồn tại của trái tim và loại bỏ trái tim khi hết thời gian
    Entity *prev = &stage.heartHead;
    for (Entity *h = stage.heartHead.next; h != NULL; h = h->next) {
        if (--h->lifetime <= 0) {
            prev->next = h->next;
            free(h);
            h = prev; // Quay lại kiểm tra thực thể tiếp theo
        }
        prev = h;
    }
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
/*Gọi các hàm xử lý logic cho người chơi, 
 các thực thể chiến đấu, và sinh ra kẻ thù.*/
static void logic(void)
{
    doBackground();
    doPlayer();
    doEnemies();
    spawnEnemies();
    //doHearts();
    //spawnHearts();
}

/*Vẽ người chơi lên màn hình.*/
static void drawPlayer(void)
{
    blit_player(player->texture, player->x, player->y);
}

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

/*Vẽ tất cả các kẻ thù lên màn hình.*/
static void drawHearts(void)
{  
   //blit_board(heart->texture, heart->x, heart->y);
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

/*Gọi các hàm vẽ để vẽ người chơi và kẻ thù lên màn hình, sau đó cập nhật renderer.*/
static void draw(void)
{
    drawBackground();
    drawPlayer();
    drawEnemies();
    drawHearts();
    SDL_RenderPresent(app.renderer); // cập nhật renderer
}

/*Giới hạn tốc độ khung hình để đảm bảo trò chơi chạy mượt mà và không quá nhanh.*/
void capFrameRate(long *then, float *remainder)
{
    long wait, frameTime;

    wait = 16 + *remainder;
    *remainder -= (int)*remainder;

    frameTime = SDL_GetTicks() - *then;
    wait -= frameTime;

    if (wait < 1) 
    {
        wait = 1;
    }

    SDL_Delay(wait);
    *remainder += 0.667;
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
   // initHeart();

    /*Khai báo tệp chứa hình kẻ thù*/
    enemyTexture = loadTexture("data\\images\\hmm.jpg");

    /*Khai báo tệp chứa ảnh nền*/
    background = loadTexture("data\\images\\jhin01.jpg");

    /*Khai báo tệp chứa ảnh trái tim*/
    heartTexture = loadTexture("data\\images\\tim.jpg");
    
    if (!enemyTexture)
     {
        fprintf(stderr, "Failed to load enemy texture: %s\n", SDL_GetError());
        exit(1);
    }

    //enemySpawnTimer = 0;
}
