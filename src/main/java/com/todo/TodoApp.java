package com.todo;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.effect.Glow;
import javafx.scene.layout.*;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;
import java.io.*;
import java.time.LocalDate;
import java.time.YearMonth;
import java.util.HashMap;
import java.util.Map;

public class TodoApp extends Application {
    private YearMonth currentMonth;
    private GridPane calendarGrid;
    private Label monthLabel;
    private Map<LocalDate, ObservableList<TodoEvent>> eventMap = new HashMap<>();
    private VBox scheduleVBox;
    private LocalDate selectedDate;
    private VBox eventDetailsPane;

    @Override
    public void start(@SuppressWarnings("exports") Stage primaryStage) {

        currentMonth = YearMonth.now();
        selectedDate = LocalDate.now();
        loadEventsFromCSV();
        BorderPane root = new BorderPane();
        HBox header = new HBox(10);
        header.setAlignment(Pos.CENTER);
        header.setPadding(new Insets(10));
        Button prevMonth = new Button("◀");
        Button nextMonth = new Button("▶");
        monthLabel = new Label();
        updateMonthLabel();
        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);
        header.getChildren().addAll(prevMonth, monthLabel, nextMonth, spacer);
        prevMonth.setOnAction(e -> changeMonth(-1));
        nextMonth.setOnAction(e -> changeMonth(1));
        calendarGrid = new GridPane();
        calendarGrid.setHgap(5);
        calendarGrid.setVgap(5);
        calendarGrid.setPadding(new Insets(10));
        updateCalendar();
        TextField titleField = new TextField();
        titleField.setPromptText("Enter event title");
        TextField descriptionField = new TextField();
        descriptionField.setPromptText("Enter event description");
        ComboBox<Integer> timeComboBox = new ComboBox<>();
        for (int hour = 8; hour <= 24; hour++) {
            timeComboBox.getItems().add(hour);
        }
        timeComboBox.setPromptText("Select time");
        timeComboBox.setValue(8);
        Button addButton = new Button("Add Event");
        addButton.setOnAction(e -> {
            String title = titleField.getText();
            String desc = descriptionField.getText();
            Integer selectedHour = timeComboBox.getValue();
            if (title != null && !title.isEmpty() && desc != null && !desc.isEmpty() && selectedHour != null) {
                eventMap.putIfAbsent(selectedDate, FXCollections.observableArrayList());
                eventMap.get(selectedDate).add(new TodoEvent(title, desc, selectedHour));
                titleField.clear();
                descriptionField.clear();
                updateSchedule(selectedDate);
                updateCalendar();
                saveEventsToCSV();
            }
        });
        VBox inputFields = new VBox(5,titleField,descriptionField);
        HBox addEventPane = new HBox(10, inputFields, timeComboBox, addButton);
        addEventPane.setAlignment(Pos.CENTER_LEFT);
        scheduleVBox = new VBox(5);
        scheduleVBox.setPadding(new Insets(10));
        updateSchedule(selectedDate);
        ScrollPane scheduleScroll = new ScrollPane(scheduleVBox);
        scheduleScroll.setFitToWidth(true);
        scheduleScroll.setPrefHeight(400);
        eventDetailsPane = new VBox(5);
        eventDetailsPane.setPadding(new Insets(10));
        VBox detailPanel = new VBox(10, addEventPane, scheduleScroll, eventDetailsPane);
        detailPanel.setPadding(new Insets(10));
        detailPanel.setPrefWidth(300);
        SplitPane centerPane = new SplitPane();
        centerPane.getItems().addAll(calendarGrid, detailPanel);
        centerPane.setDividerPositions(0.7);
        root.setTop(header);
        root.setCenter(centerPane);
        Scene scene = new Scene(root, 1000, 700);
        primaryStage.setTitle("To-Do App");
        primaryStage.setMaximized(true);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void updateMonthLabel() {
        monthLabel.setText(currentMonth.getMonth().toString() + " " + currentMonth.getYear());
    }

    private void updateCalendar() {
        calendarGrid.getChildren().clear();
        String[] weekdays = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        for (int i = 0; i < weekdays.length; i++) {
            Label lbl = new Label(weekdays[i]);
            lbl.setStyle("-fx-font-weight: bold; -fx-font-size: 14px;");
            lbl.setAlignment(Pos.CENTER);
            lbl.setMaxWidth(Double.MAX_VALUE);
            calendarGrid.add(lbl, i, 0);
        }
        LocalDate firstDayOfMonth = currentMonth.atDay(1);
        int startDayOfWeek = firstDayOfMonth.getDayOfWeek().getValue() % 7;
        int daysInMonth = currentMonth.lengthOfMonth();
        for (int day = 1; day <= daysInMonth; day++) {
            LocalDate date = currentMonth.atDay(day);
            VBox dayCell = new VBox(5);
            dayCell.setPadding(new Insets(5));
            dayCell.setPrefSize(120, 100);
            dayCell.setStyle("-fx-border-color: #ccc; -fx-background-color: #f9f9f9;");
            Label dayLabel = new Label(String.valueOf(day));
            dayLabel.setStyle("-fx-font-weight: bold;");
            dayCell.getChildren().add(dayLabel);
            if (eventMap.containsKey(date) && !eventMap.get(date).isEmpty()) {
                Circle dot = new Circle(4);
                dot.setStyle("-fx-fill: red;");
                dayCell.getChildren().add(dot);
            }
            if (date.equals(selectedDate)) {
                dayCell.setEffect(new Glow(0.8));
            } else {
                dayCell.setEffect(null);
            }
            dayCell.setOnMouseClicked(e -> {
                selectedDate = date;
                updateSchedule(date);
                updateCalendar();
            });
            int col = (startDayOfWeek + day - 1) % 7;
            int row = ((startDayOfWeek + day - 1) / 7) + 1;
            calendarGrid.add(dayCell, col, row);
        }
    }

    private void updateSchedule(LocalDate date) {
        scheduleVBox.getChildren().clear();
        
        ObservableList<TodoEvent> events = eventMap.getOrDefault(date, FXCollections.observableArrayList());
    
        for (int hour = 8; hour <= 24; hour++) {
            HBox row = new HBox(10);
            row.setPadding(new Insets(5));
            row.setStyle("-fx-border-color: #ddd; -fx-border-width: 0 0 1 0;");
    
            Label timeLabel = new Label(String.format("%02d:00", hour));
            timeLabel.setPrefWidth(60);
    
            StringBuilder eventsStr = new StringBuilder();
            for (TodoEvent event : events) {
                if (event.getHour() == hour) {
                    if (eventsStr.length() > 0) {
                        eventsStr.append(", ");
                    }
                    eventsStr.append(event.getTitle());
                }
            }
    
            Label eventLabel = new Label(eventsStr.toString());
            row.getChildren().addAll(timeLabel, eventLabel);
            scheduleVBox.getChildren().add(row);
        }
    }
    
    private void changeMonth(int offset) {
        currentMonth = currentMonth.plusMonths(offset);
        updateMonthLabel();
        updateCalendar();
    }

    private void saveEventsToCSV() {
        try (PrintWriter writer = new PrintWriter(new FileWriter("events.csv"))) {
            writer.println("Date,Hour,Title,Description");
            for (Map.Entry<LocalDate, ObservableList<TodoEvent>> entry : eventMap.entrySet()) {
                LocalDate date = entry.getKey();
                for (TodoEvent event : entry.getValue()) {
                    writer.printf("%s,%d,%s,%s%n", date, event.getHour(), event.getTitle(), event.getDescription());
                }
            }
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Error saving CSV: " + e.getMessage(), ButtonType.OK);
            alert.showAndWait();
        }
    }

    private void loadEventsFromCSV() {
        File file = new File("events.csv");
        if (!file.exists()) return;
        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line = reader.readLine();
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",", 4);
                if (parts.length == 4) {
                    LocalDate date = LocalDate.parse(parts[0]);
                    int hour = Integer.parseInt(parts[1]);
                    String title = parts[2];
                    String desc = parts[3];
                    eventMap.putIfAbsent(date, FXCollections.observableArrayList());
                    eventMap.get(date).add(new TodoEvent(title, desc, hour));
                }
            }
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Error loading CSV: " + e.getMessage(), ButtonType.OK);
            alert.showAndWait();
        }
    }

    public static class TodoEvent {
        private String title;
        private String description;
        private int hour;
        public TodoEvent(String title, String description, int hour) {
            this.title = title;
            this.description = description;
            this.hour = hour;
        }
        public String getTitle() { return title; }
        public String getDescription() { return description; }
        public int getHour() { return hour; }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
