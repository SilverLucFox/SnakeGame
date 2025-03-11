module com.todo {
    requires javafx.controls;
    requires javafx.fxml;

    opens com.todo to javafx.fxml;
    exports com.todo;
}
