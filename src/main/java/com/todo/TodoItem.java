package com.todo;

import java.time.LocalDate;

public class TodoItem {
    private String task;
    private LocalDate dueDate;

    public TodoItem(String task, LocalDate dueDate) {
        this.task = task;
        this.dueDate = dueDate;
    }

    public String getTask() {
        return task;
    }

    public LocalDate getDueDate() {
        return dueDate;
    }
}
