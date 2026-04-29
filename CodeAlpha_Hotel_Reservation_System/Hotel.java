import java.io.*;
import java.util.*;

class Room {
    int roomNumber;
    String category;
    boolean isBooked;

    Room(int roomNumber, String category) {
        this.roomNumber = roomNumber;
        this.category = category;
        this.isBooked = false;
    }

    public String toString() {
        return roomNumber + "," + category + "," + isBooked;
    }
}

class Booking {
    String customerName;
    int roomNumber;
    String category;

    Booking(String customerName, int roomNumber, String category) {
        this.customerName = customerName;
        this.roomNumber = roomNumber;
        this.category = category;
    }

    public String toString() {
        return customerName + "," + roomNumber + "," + category;
    }
}

public class Hotel{
    static List<Room> rooms = new ArrayList<>();
    static List<Booking> bookings = new ArrayList<>();

    static final String ROOM_FILE = "rooms.txt";
    static final String BOOKING_FILE = "bookings.txt";

    public static void main(String[] args) {
        loadRooms();
        loadBookings();

        Scanner sc = new Scanner(System.in);
        int choice;

        do {
            System.out.println("\n===== HOTEL RESERVATION SYSTEM =====");
            System.out.println("1. View Available Rooms");
            System.out.println("2. Book Room");
            System.out.println("3. Cancel Booking");
            System.out.println("4. View Bookings");
            System.out.println("5. Exit");
            System.out.print("Enter choice: ");
            choice = sc.nextInt();

            switch (choice) {
                case 1: viewAvailableRooms(); break;
                case 2: bookRoom(sc); break;
                case 3: cancelBooking(sc); break;
                case 4: viewBookings(); break;
                case 5: saveData(); System.out.println("Exiting..."); break;
                default: System.out.println("Invalid choice!");
            }

        } while (choice != 5);
    }

    // Load Rooms
    static void loadRooms() {
        File file = new File(ROOM_FILE);

        if (!file.exists()) {
            // Default rooms
            rooms.add(new Room(101, "Standard"));
            rooms.add(new Room(102, "Deluxe"));
            rooms.add(new Room(103, "Suite"));
            saveRooms();
        } else {
            try (BufferedReader br = new BufferedReader(new FileReader(file))) {
                String line;
                while ((line = br.readLine()) != null) {
                    String[] data = line.split(",");
                    Room r = new Room(Integer.parseInt(data[0]), data[1]);
                    r.isBooked = Boolean.parseBoolean(data[2]);
                    rooms.add(r);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    // Load Bookings
    static void loadBookings() {
        File file = new File(BOOKING_FILE);

        if (!file.exists()) return;

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split(",");
                bookings.add(new Booking(data[0], Integer.parseInt(data[1]), data[2]));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // Save Rooms
    static void saveRooms() {
        try (PrintWriter pw = new PrintWriter(new FileWriter(ROOM_FILE))) {
            for (Room r : rooms) {
                pw.println(r);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // Save Bookings
    static void saveBookings() {
        try (PrintWriter pw = new PrintWriter(new FileWriter(BOOKING_FILE))) {
            for (Booking b : bookings) {
                pw.println(b);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    static void saveData() {
        saveRooms();
        saveBookings();
    }

    // View Available Rooms
    static void viewAvailableRooms() {
        System.out.println("\nAvailable Rooms:");
        for (Room r : rooms) {
            if (!r.isBooked) {
                System.out.println("Room No: " + r.roomNumber + " | " + r.category);
            }
        }
    }

    // Book Room
    static void bookRoom(Scanner sc) {
        System.out.print("Enter your name: ");
        sc.nextLine();
        String name = sc.nextLine();

        System.out.print("Enter room category (Standard/Deluxe/Suite): ");
        String category = sc.nextLine();

        for (Room r : rooms) {
            if (!r.isBooked && r.category.equalsIgnoreCase(category)) {

                // Payment Simulation
                System.out.println("Processing payment...");
                System.out.println("Payment successful!");

                r.isBooked = true;
                bookings.add(new Booking(name, r.roomNumber, r.category));

                System.out.println("Room booked successfully! Room No: " + r.roomNumber);
                return;
            }
        }

        System.out.println("No rooms available in this category!");
    }

    // Cancel Booking
    static void cancelBooking(Scanner sc) {
        System.out.print("Enter your name: ");
        sc.nextLine();
        String name = sc.nextLine();

        Iterator<Booking> it = bookings.iterator();

        while (it.hasNext()) {
            Booking b = it.next();
            if (b.customerName.equalsIgnoreCase(name)) {

                for (Room r : rooms) {
                    if (r.roomNumber == b.roomNumber) {
                        r.isBooked = false;
                    }
                }

                it.remove();
                System.out.println("Booking cancelled!");
                return;
            }
        }

        System.out.println("Booking not found!");
    }

    // View Bookings
    static void viewBookings() {
        System.out.println("\nAll Bookings:");
        for (Booking b : bookings) {
            System.out.println("Name: " + b.customerName +
                    " | Room: " + b.roomNumber +
                    " | Category: " + b.category);
        }
    }
}