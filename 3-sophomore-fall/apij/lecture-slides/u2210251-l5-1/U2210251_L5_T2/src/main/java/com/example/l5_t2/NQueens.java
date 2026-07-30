package com.example.l5_t2;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

public class NQueens extends Application {
    private int[] queens;
    private int boardSize;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        getUserInput();
        solveNQueens(0);
        displayChessBoard(primaryStage);
    }
    private void getUserInput() {
        //for simplicity, I'm hardcoded the board size here
        boardSize = 8; //can change this value
        queens = new int[boardSize];
    }
    private void solveNQueens(int row) {
        if (row == boardSize) {
            return;
        }
        for (int col = 0; col < boardSize; col++) {
            if (isSafe(row, col)) {
                queens[row] = col;
                solveNQueens(row + 1);
            }
        }
    }
    private boolean isSafe(int row, int col) {
        for (int prevRow = 0; prevRow < row; prevRow++) {
            int prevCol = queens[prevRow];
            if (prevCol == col || Math.abs(prevRow - row) == Math.abs(prevCol - col)) {
                return false;
            }
        }
        return true;
    }
    private void displayChessBoard(Stage primaryStage) {
        GridPane gridPane = new GridPane();
        for (int row = 0; row < boardSize; row++) {
            for (int col = 0; col < boardSize; col++) {
                Rectangle square = new Rectangle(50, 50);
                if ((row + col) % 2 == 0) {
                    square.setFill(Color.LIGHTGRAY);
                } else {
                    square.setFill(Color.DARKGRAY);
                }
                gridPane.add(square, col, row);
            }
        }
        for (int i = 0; i < boardSize; i++) {
            int queenCol = queens[i];
            Rectangle queen = new Rectangle(50, 50);
            queen.setFill(Color.PURPLE);
            gridPane.add(queen, queenCol, i);
        }
        
        Scene scene = new Scene(gridPane);
        primaryStage.setTitle("N-Queens Puzzle");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
