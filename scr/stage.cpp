#include "stage.h"

extern App app;

Stage stage;

Entity *player;
SDL_Texture *enemyTexture, *friendTexture;
int enemySpawnTimer = 0, friendSpawnTimer = 0;

/*Khởi tạo người chơi, bao gồm việc cấp phát bộ nhớ,
// thiết lập vị trí ban đầu, và tải texture cho người chơi.*/
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

    player->x = 50;
    player->y = 50;
    player->texture = loadTexture("data\\images\\hmm.jpg");
    if (!player->texture) 
    {
        fprintf(stderr, "Failed to load player texture: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

/*Xử lý logic di chuyển cho tất cả các thực thể chiến đấu (bao gồm cả người chơi và kẻ thù). 
//Xóa các thực thể ra khỏi màn hình.*/
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

static const int ENEMY_SPAWN_GAP = 100; // Khoảng cách cố định giữa các kẻ thù
int lastEnemyType = -1; // -1: chưa có kẻ thù nào, 0: loại kẻ thù gốc, 1: loại kẻ thù mới

/*Sinh ra kẻ thù mới tại các vị trí ngẫu nhiên trên màn hình 
//sau một khoảng thời gian nhất định.*/
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
        enemy->y = SCREEN_HEIGHT; // Đặt vị trí y của kẻ thù ở cuối màn hình

        // Randomly choose between the original enemy and the new enemy, ensuring they are not consecutive
        int enemyType;
        do {
            enemyType = rand() % 2;
        } while (enemyType == lastEnemyType);

        if (enemyType == 0) 
        {
            enemy->texture = enemyTexture;
            enemy->dy = BOARD_SPEED; // Tốc độ di chuyển cố định của kẻ thù gốc
        } 

        else 
        {
            enemy->texture = friendTexture;
            enemy->dy = BOARD_SPEED; // Tốc độ di chuyển cố định của kẻ thù mới
        }

        lastEnemyType = enemyType; // Cập nhật loại kẻ thù cuối cùng

        // Đặt thời gian sinh kẻ thù mới dựa trên khoảng cách cố định và tốc độ di chuyển
        enemySpawnTimer = ENEMY_SPAWN_GAP / abs(enemy->dy); 
    }
}

/*Xử lý logic di chuyển của người chơi dựa trên đầu vào từ bàn phím. 
//Cập nhật vị trí của người chơi dựa trên tốc độ di chuyển.*/
static void doPlayer(void)
{
    player->dx = player->dy = 0;

    if (player->reload > 0) 
    {
        player->reload--;
    }

    if (app.keyboard[SDL_SCANCODE_UP] && player->y >= 0 ) 
    {
        player->dy = -PLAYER_SPEED;
    }

    if (app.keyboard[SDL_SCANCODE_DOWN] && player->y <= SCREEN_HEIGHT-PLAYER_HEIGHT) 
    {
        player->dy = PLAYER_SPEED;
    }

    if (app.keyboard[SDL_SCANCODE_LEFT] && player->x >= 0) 
    {
        player->dx = -PLAYER_SPEED;
    }

    if (app.keyboard[SDL_SCANCODE_RIGHT] && player->x <= SCREEN_WIDTH-PLAYER_WIDTH) 
    {
        player->dx = PLAYER_SPEED;
    }

    // Apply gravity
    player->gravitySpeed += GRAVITY;
    if (player->gravitySpeed > MAX_FALL_SPEED) 
    {
        player->gravitySpeed = MAX_FALL_SPEED;
    }
    player->y += player->gravitySpeed;

    // Update player position
    player->x += player->dx;
    player->y += player->dy;

    // Kiểm tra va chạm giữa người chơi và kẻ thù
    /*for (Entity *e = stage.enemyHead.next; e != NULL; e = e->next)
    {
        if (e != player && player->y + player->h >= e->y && player->x == e->x)
        {
            // Đặt lại vị trí y để đứng trên bề mặt của kẻ thù
            player->y = e->y - player->h;
            player->gravitySpeed = 0; // Reset tốc độ rơi

            // Đặt lại vị trí x để bị kéo theo
            player->x = e->x;
        }
        else
        {
            player->x += player->dx;
            player->y += player->dy;
        }
    }*/

}

//Gọi các hàm xử lý logic cho người chơi, các thực thể chiến đấu, và sinh ra kẻ thù.
static void logic(void)
{
    doPlayer();
    doEnemies();
    //doBullets();
    spawnEnemies();
}

//Vẽ người chơi lên màn hình.
static void drawPlayer(void)
{
    blit_player(player->texture, player->x, player->y);
}

//Vẽ tất cả các kẻ thù lên màn hình.
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

static void drawFriends(void)
{
    Entity *b;

    for (b = stage.boardHead.next; b != NULL; b = b->next) 
    {
        blit_board(b->texture, b->x, b->y);
    }
}

//Gọi các hàm vẽ để vẽ người chơi và kẻ thù lên màn hình, sau đó cập nhật renderer.
static void draw(void)
{
    drawPlayer();
    drawEnemies();
    drawFriends();
    SDL_RenderPresent(app.renderer); // cập nhật renderer
}

//Giới hạn tốc độ khung hình để đảm bảo trò chơi chạy mượt mà và không quá nhanh.
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
    stage.boardTail = &stage.boardHead;

    initPlayer();

    friendTexture = loadTexture("data\\images\\background.jpg");
    enemyTexture = loadTexture("data\\images\\monster.jpg");
    if (!enemyTexture)
     {
        fprintf(stderr, "Failed to load enemy texture: %s\n", SDL_GetError());
        exit(1);
    }

    enemySpawnTimer = 0;
}
