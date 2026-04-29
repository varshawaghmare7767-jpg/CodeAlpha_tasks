import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

class Student {
    String name;
    ArrayList<Integer> grades;

    Student(String name) {
        this.name = name;
        grades = new ArrayList<>();
    }

    void addGrade(int grade) {
        grades.add(grade);
    }

    double getAverage() {
        if (grades.isEmpty()) return 0;
        int sum = 0;
        for (int g : grades) sum += g;
        return (double) sum / grades.size();
    }

    int getHighest() {
        return Collections.max(grades);
    }

    int getLowest() {
        return Collections.min(grades);
    }

    String getReport() {
        StringBuilder sb = new StringBuilder();
        sb.append("Name: ").append(name).append("\n");
        sb.append("Grades: ").append(grades).append("\n");

        if (!grades.isEmpty()) {
            sb.append("Average: ").append(getAverage()).append("\n");
            sb.append("Highest: ").append(getHighest()).append("\n");
            sb.append("Lowest: ").append(getLowest()).append("\n");
        } else {
            sb.append("No grades available\n");
        }
        sb.append("------------------------\n");
        return sb.toString();
    }
}

public class StudentGUI extends JFrame {
    private ArrayList<Student> students = new ArrayList<>();

    private JTextField nameField, gradeField;
    private JTextArea outputArea;

    public StudentGUI() {
        setTitle("Student Grade Manager");
        setSize(500, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Top Panel
        JPanel topPanel = new JPanel(new GridLayout(3, 2));
        topPanel.add(new JLabel("Student Name:"));
        nameField = new JTextField();
        topPanel.add(nameField);

        topPanel.add(new JLabel("Grade:"));
        gradeField = new JTextField();
        topPanel.add(gradeField);

        JButton addStudentBtn = new JButton("Add Student");
        JButton addGradeBtn = new JButton("Add Grade");

        topPanel.add(addStudentBtn);
        topPanel.add(addGradeBtn);

        add(topPanel, BorderLayout.NORTH);

        // Center Output Area
        outputArea = new JTextArea();
        outputArea.setEditable(false);
        add(new JScrollPane(outputArea), BorderLayout.CENTER);

        // Bottom Panel
        JPanel bottomPanel = new JPanel();
        JButton showReportBtn = new JButton("Show Report");
        bottomPanel.add(showReportBtn);
        add(bottomPanel, BorderLayout.SOUTH);

        // Button Actions
        addStudentBtn.addActionListener(e -> {
            String name = nameField.getText().trim();
            if (!name.isEmpty()) {
                students.add(new Student(name));
                outputArea.append("Student added: " + name + "\n");
                nameField.setText("");
            } else {
                JOptionPane.showMessageDialog(this, "Enter student name!");
            }
        });

        addGradeBtn.addActionListener(e -> {
            String name = nameField.getText().trim();
            String gradeText = gradeField.getText().trim();

            if (name.isEmpty() || gradeText.isEmpty()) {
                JOptionPane.showMessageDialog(this, "Enter name and grade!");
                return;
            }

            try {
                int grade = Integer.parseInt(gradeText);
                boolean found = false;

                for (Student s : students) {
                    if (s.name.equalsIgnoreCase(name)) {
                        s.addGrade(grade);
                        outputArea.append("Grade added to " + name + "\n");
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    JOptionPane.showMessageDialog(this, "Student not found!");
                }

                gradeField.setText("");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Invalid grade!");
            }
        });

        showReportBtn.addActionListener(e -> {
            outputArea.setText("=== Student Report ===\n");
            for (Student s : students) {
                outputArea.append(s.getReport());
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new StudentGUI().setVisible(true);
        });
    }
}