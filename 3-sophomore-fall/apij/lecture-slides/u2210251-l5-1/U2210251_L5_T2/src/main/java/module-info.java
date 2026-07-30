module com.example.l5_t2 {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.l5_t2 to javafx.fxml;
    exports com.example.l5_t2;
}