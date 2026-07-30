import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class KnightsTourSolverGUI extends JFrame implements ActionListener, KeyListener {

    private int[][] solution;
    private int moveNumber = 1;
    private int boardSize;
    private int currentRow;
    private int currentCol;

    private JButton[][] boardButtons;

    public KnightsTourSolverGUI() {
        setTitle("Knight's Tour Solver");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Step 1: Ask the user to enter the dimension n for the chessboard (n x n)
        String input = JOptionPane.showInputDialog("Enter the dimension n for the chessboard (n x n):");
        try {
            boardSize = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Invalid input. Please enter a valid integer.", "Error", JOptionPane.ERROR_MESSAGE);
            System.exit(1);
        }

        // Step 2: Ask the user to enter the initial position for the knight
        input = JOptionPane.showInputDialog("Enter the initial row for the knight (0 to " + (boardSize - 1) + "):");
        try {
            currentRow = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Invalid input. Please enter a valid integer.", "Error", JOptionPane.ERROR_MESSAGE);
            System.exit(1);
        }

        input = JOptionPane.showInputDialog("Enter the initial column for the knight (0 to " + (boardSize - 1) + "):");
        try {
            currentCol = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Invalid input. Please enter a valid integer.", "Error", JOptionPane.ERROR_MESSAGE);
            System.exit(1);
        }

        setSize(50 * boardSize, 50 * boardSize);
        setLocationRelativeTo(null);

        initUI();
        solveKnightsTour();

        addKeyListener(this);
        setFocusable(true);

        setVisible(true);
    }

    private void initUI() {
        setLayout(new GridLayout(boardSize, boardSize));
        boardButtons = new JButton[boardSize][boardSize];

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                JButton button = new JButton();
                button.setPreferredSize(new Dimension(50, 50));
                button.setEnabled(false);
                boardButtons[i][j] = button;
                add(button);
            }
        }
        currentRow = 0;
        currentCol = 0;
    }

    private void solveKnightsTour() {
        solution = new int[boardSize][boardSize];
        if (solve(currentRow, currentCol, moveNumber)) {
            displaySolution();
        } else {
            JOptionPane.showMessageDialog(this, "No solution found", "Knight's Tour", JOptionPane.INFORMATION_MESSAGE);
            System.exit(0);
        }
    }

    private boolean solve(int row, int col, int moveNumber) {
        if (moveNumber == boardSize * boardSize + 1) {
            return true; // All squares visited
        }

        if (row >= 0 && col >= 0 && row < boardSize && col < boardSize && solution[row][col] == 0) {
            solution[row][col] = moveNumber;
            boardButtons[row][col].setText(String.valueOf(moveNumber));

            int[] moveRow = {2, 1, -1, -2, -2, -1, 1, 2};
            int[] moveCol = {1, 2, 2, 1, -1, -2, -2, -1};

            for (int i = 0; i < 8; i++) {
                if (solve(row + moveRow[i], col + moveCol[i], moveNumber + 1)) {
                    drawLine(row, col, row + moveRow[i], col + moveCol[i]);
                    return true;
                }
            }

            // Backtrack
            solution[row][col] = 0;
            boardButtons[row][col].setText("");
        }

        return false;
    }

    private void drawLine(int startRow, int startCol, int endRow, int endCol) {
        repaint();
    }

    private void displaySolution() {
        JOptionPane.showMessageDialog(this, "Knight's Tour Successfully Solved!", "Knight's Tour", JOptionPane.INFORMATION_MESSAGE);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // Not used in this example
    }

    @Override
    public void keyPressed(KeyEvent e) {
        // Check if the pressed key is the space bar
        if (e.getKeyCode() == KeyEvent.VK_SPACE) {
            moveKnight();
        }
    }

    private void moveKnight() {
        moveNumber++;
        if (moveNumber <= boardSize * boardSize) {
            drawLine(currentRow, currentCol, solution[currentRow][currentCol], solution[currentRow][currentCol + 1]);
            currentRow = solution[currentRow][currentCol];
            currentCol = solution[currentRow][currentCol + 1];
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
        // Not used in this example
    }

    @Override
    public void keyTyped(KeyEvent e) {
        // Not used in this example
    }


    protected void paintComponent(Graphics g) {
        super.paintComponents(g);
        int cellSize = 50;
        g.setColor(Color.RED);
        g.drawLine(currentCol * cellSize + cellSize / 2, currentRow * cellSize + cellSize / 2,
                (currentCol + 1) * cellSize + cellSize / 2, currentRow * cellSize + cellSize / 2);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new KnightsTourSolverGUI());
    }
}
