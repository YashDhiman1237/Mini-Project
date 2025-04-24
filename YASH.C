#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define INF 9999

// Linked List for Menu
struct MenuItem {
    char name[50];
    int price;
    struct MenuItem* next;
};

struct MenuItem* menuHead = NULL;

void addMenuItem(char name[], int price) {
    struct MenuItem* newItem = (struct MenuItem*)malloc(sizeof(struct MenuItem));
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->next = menuHead;
    menuHead = newItem;
}

void displayMenu() {
    struct MenuItem* temp = menuHead;
    printf("\n--- Menu ---\n");
    while (temp != NULL) {
        printf("%s - ₹%d\n", temp->name, temp->price);
        temp = temp->next;
    }
}

// Queue for Orders
struct Order {
    char item[50];
    struct Order* next;
};

struct Order *front = NULL, *rear = NULL;

void enqueue(char item[]) {
    struct Order* newOrder = (struct Order*)malloc(sizeof(struct Order));
    strcpy(newOrder->item, item);
    newOrder->next = NULL;
    if (rear == NULL) {
        front = rear = newOrder;
    } else {
        rear->next = newOrder;
        rear = newOrder;
    }
}

void dequeue() {
    if (front == NULL) {
        printf("No orders to serve.\n");
        return;
    }
    struct Order* temp = front;
    printf("Order served: %s\n", temp->item);
    front = front->next;
    if (front == NULL) rear = NULL;
    free(temp);
}

void displayOrders() {
    struct Order* temp = front;
    printf("\n--- Current Orders ---\n");
    if (!temp) {
        printf("No orders in queue.\n");
        return;
    }
    while (temp != NULL) {
        printf("- %s\n", temp->item);
        temp = temp->next;
    }
}

// Graph for Routes
int graph[MAX][MAX];
char locations[MAX][50];
int num_locations = 0;

int getIndex(char name[]) {
    for (int i = 0; i < num_locations; i++) {
        if (strcmp(locations[i], name) == 0)
            return i;
    }
    strcpy(locations[num_locations], name);
    return num_locations++;
}

void addEdge(char src[], char dest[], int weight) {
    int u = getIndex(src);
    int v = getIndex(dest);
    graph[u][v] = weight;
    graph[v][u] = weight;
}

void dijkstra(int start) {
    int dist[MAX], visited[MAX] = {0};
    for (int i = 0; i < num_locations; i++) dist[i] = INF;
    dist[start] = 0;

    for (int count = 0; count < num_locations - 1; count++) {
        int min = INF, u = -1;
        for (int i = 0; i < num_locations; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < num_locations; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\n--- Shortest Paths from %s ---\n", locations[start]);
    for (int i = 0; i < num_locations; i++) {
        printf("%s -> %s = %d\n", locations[start], locations[i], dist[i]);
    }
}

// Main
int main() {
    // Setup Menu
    addMenuItem("Pizza", 150);
    addMenuItem("Burger", 100);
    addMenuItem("Pasta", 120);

    // Display menu
    displayMenu();

    // Take orders
    enqueue("Pizza");
    enqueue("Burger");
    displayOrders();

    // Serve one order
    dequeue();
    displayOrders();

    // Setup Graph
    addEdge("Restaurant", "Customer1", 4);
    addEdge("Restaurant", "Customer2", 2);
    addEdge("Customer1", "Customer2", 1);
    addEdge("Customer2", "Customer3", 7);
    addEdge("Restaurant", "Customer3", 10);

    // Calculate shortest path
    dijkstra(getIndex("Restaurant"));

    return 0;
}
