#include "raylib.h"
#include <vector>
#include <string>

long long int compute(const std::vector<std::vector<int>>& v, int row, int col, int& startX, int& startY) {
    long long int max = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            long long int sum = v[i][j];
           
            int nx = i - 1;
            int ny = j + 1;
            while (nx >= 0 && ny < col) {
                sum += v[nx][ny];
                nx--;
                ny++;
            }
            
            nx = i - 1;
            ny = j - 1;
            while (nx >= 0 && ny >= 0) {
                sum += v[nx][ny];
                nx--;
                ny--;
            }
            
            nx = i + 1;
            ny = j + 1;
            while (nx < row && ny < col) {
                sum += v[nx][ny];
                nx++;
                ny++;
            }
          
            nx = i + 1;
            ny = j - 1;
            while (nx < row && ny >= 0) {
                sum += v[nx][ny];
                nx++;
                ny--;
            }

            if (sum > max) {
                max = sum;
                startX = i;
                startY = j;
            }
        }
    }
    return max;
}

int main() {
   
    std::vector<std::vector<int>> v = {
        {1, 2, 2,1},
        {2, 4, 2,4},
        {2, 2, 3, 1},
        {2, 4, 2, 4}
    };
    int rows = v.size();
    int cols = v[0].size();

    const int cellSize = 50;
    const int screenWidth = cols * cellSize + 200;  
    const int screenHeight = rows * cellSize + 100;

    InitWindow(screenWidth, screenHeight, "X-Sum ");
    SetTargetFPS(60);

    int selectedX = 0;
    int selectedY = 0;
    int startX = 0;
    int startY = 0;
    long long int maxSum = compute(v, rows, cols, startX, startY);
    bool showPaths = false;

    while (!WindowShouldClose()) {
       
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            selectedX = mousePos.y / cellSize;
            selectedY = mousePos.x / cellSize;
            if (selectedX < rows && selectedY < cols) {
                showPaths = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
               
                DrawRectangle(j * cellSize, i * cellSize, cellSize - 1, cellSize - 1, LIGHTGRAY);

                
                std::string num = std::to_string(v[i][j]);
                DrawText(num.c_str(),
                    j * cellSize + cellSize / 2 - MeasureText(num.c_str(), 20) / 2,
                    i * cellSize + cellSize / 2 - 10,
                    20, BLACK);
            }
        }

        
        if (showPaths && selectedX >= 0 && selectedX < rows && selectedY >= 0 && selectedY < cols) {
            
            DrawRectangle(selectedY * cellSize, selectedX * cellSize, cellSize - 1, cellSize - 1,
                Fade(YELLOW, 0.5f));

            
            long long int sum = v[selectedX][selectedY];

           
            int nx = selectedX - 1;
            int ny = selectedY + 1;
            while (nx >= 0 && ny < cols) {
                DrawRectangle(ny * cellSize, nx * cellSize, cellSize - 1, cellSize - 1, Fade(BLUE, 0.5f));
                sum += v[nx][ny];
                nx--;
                ny++;
            }

            
            nx = selectedX - 1;
            ny = selectedY - 1;
            while (nx >= 0 && ny >= 0) {
                DrawRectangle(ny * cellSize, nx * cellSize, cellSize - 1, cellSize - 1, Fade(GREEN, 0.5f));
                sum += v[nx][ny];
                nx--;
                ny--;
            }

            
            nx = selectedX + 1;
            ny = selectedY + 1;
            while (nx < rows && ny < cols) {
                DrawRectangle(ny * cellSize, nx * cellSize, cellSize - 1, cellSize - 1, Fade(RED, 0.5f));
                sum += v[nx][ny];
                nx++;
                ny++;
            }

           
            nx = selectedX + 1;
            ny = selectedY - 1;
            while (nx < rows && ny >= 0) {
                DrawRectangle(ny * cellSize, nx * cellSize, cellSize - 1, cellSize - 1, Fade(PURPLE, 0.5f));
                sum += v[nx][ny];
                nx++;
                ny--;
            }

           
            std::string sumText = "Current Sum: " + std::to_string(sum);
            DrawText(sumText.c_str(), cols * cellSize + 10, 20, 20, BLACK);
        }

        
        std::string maxText = "Max Sum: " + std::to_string(maxSum);
        DrawText(maxText.c_str(), cols * cellSize + 10, 50, 20, DARKGREEN);

        
        DrawText("Click a cell to see its diagonal sums", 10, screenHeight - 30, 20, DARKGRAY);

        EndDrawing();
    }

    
    return 0;
}