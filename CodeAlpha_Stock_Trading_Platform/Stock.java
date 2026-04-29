import java.util.*;

// Stock Class
class Stock {
    String name;
    double price;

    Stock(String name, double price) {
        this.name = name;
        this.price = price;
    }
}

// Portfolio Class
class Portfolio {
    HashMap<String, Integer> holdings = new HashMap<>();

    void buyStock(String stockName, int quantity) {
        holdings.put(stockName, holdings.getOrDefault(stockName, 0) + quantity);
    }

    void sellStock(String stockName, int quantity) {
        if (holdings.containsKey(stockName)) {
            int current = holdings.get(stockName);
            if (quantity <= current) {
                holdings.put(stockName, current - quantity);
                if (holdings.get(stockName) == 0)
                    holdings.remove(stockName);
            } else {
                System.out.println("Not enough shares to sell!");
            }
        } else {
            System.out.println("Stock not found in portfolio!");
        }
    }

    void displayPortfolio(ArrayList<Stock> market) {
        double total = 0;
        System.out.println("\n--- Portfolio ---");
        for (String stockName : holdings.keySet()) {
            int qty = holdings.get(stockName);
            double price = 0;

            for (Stock s : market) {
                if (s.name.equalsIgnoreCase(stockName)) {
                    price = s.price;
                    break;
                }
            }

            double value = qty * price;
            total += value;

            System.out.println(stockName + " | Qty: " + qty + " | Value: " + value);
        }
        System.out.println("Total Portfolio Value: " + total);
    }
}

// User Class
class User {
    String name;
    double balance;
    Portfolio portfolio;

    User(String name, double balance) {
        this.name = name;
        this.balance = balance;
        portfolio = new Portfolio();
    }

    void buy(Stock stock, int qty) {
        double cost = stock.price * qty;
        if (balance >= cost) {
            balance -= cost;
            portfolio.buyStock(stock.name, qty);
            System.out.println("Bought " + qty + " shares of " + stock.name);
        } else {
            System.out.println("Insufficient balance!");
        }
    }

    void sell(Stock stock, int qty) {
        portfolio.sellStock(stock.name, qty);
        balance += stock.price * qty;
        System.out.println("Sold " + qty + " shares of " + stock.name);
    }
}

// Main Class
public class StockTradingApp {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Market Data
        ArrayList<Stock> market = new ArrayList<>();
        market.add(new Stock("TCS", 3500));
        market.add(new Stock("INFY", 1500));
        market.add(new Stock("RELIANCE", 2500));

        // User
        User user = new User("Kusum", 100000);

        while (true) {
            System.out.println("\n--- Stock Trading Platform ---");
            System.out.println("1. View Market");
            System.out.println("2. Buy Stock");
            System.out.println("3. Sell Stock");
            System.out.println("4. View Portfolio");
            System.out.println("5. Exit");
            System.out.print("Enter choice: ");
            int ch = sc.nextInt();

            switch (ch) {
                case 1:
                    System.out.println("\n--- Market Data ---");
                    for (Stock s : market) {
                        System.out.println(s.name + " : ₹" + s.price);
                    }
                    break;

                case 2:
                    System.out.print("Enter stock name: ");
                    String buyName = sc.next();
                    System.out.print("Enter quantity: ");
                    int buyQty = sc.nextInt();

                    boolean foundBuy = false;
                    for (Stock s : market) {
                        if (s.name.equalsIgnoreCase(buyName)) {
                            user.buy(s, buyQty);
                            foundBuy = true;
                            break;
                        }
                    }
                    if (!foundBuy) System.out.println("Stock not found!");
                    break;

                case 3:
                    System.out.print("Enter stock name: ");
                    String sellName = sc.next();
                    System.out.print("Enter quantity: ");
                    int sellQty = sc.nextInt();

                    boolean foundSell = false;
                    for (Stock s : market) {
                        if (s.name.equalsIgnoreCase(sellName)) {
                            user.sell(s, sellQty);
                            foundSell = true;
                            break;
                        }
                    }
                    if (!foundSell) System.out.println("Stock not found!");
                    break;

                case 4:
                    user.portfolio.displayPortfolio(market);
                    System.out.println("Balance: ₹" + user.balance);
                    break;

                case 5:
                    System.out.println("Exiting...");
                    return;

                default:
                    System.out.println("Invalid choice!");
            }
        }
    }
}