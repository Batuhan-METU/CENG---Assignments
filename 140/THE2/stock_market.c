#include "stock_market.h"

Person* create_person(char *name, int id) {
    /* WRITE YOUR CODE HERE AND REMOVE RETURN NULL */
    return NULL;
}

Company* create_company(char *name, char *abbr, int order) {
    /* WRITE YOUR CODE HERE AND REMOVE RETURN NULL */
    return NULL;
}

void add_company_to_market(StockMarket *market, Company *company) {
    /* WRITE YOUR CODE HERE */
}

RequestNode* create_request_node(Person *p, int amount, float price) {
    /* WRITE YOUR CODE HERE AND REMOVE RETURN NULL */
    return NULL;
}

void insert_sorted(RequestNode **head, RequestNode *node, int ascending) {
    /* WRITE YOUR CODE HERE */
}

void insert_buy_request(StockMarket *market, Person **people, int people_count, char *buyer_name, char *company_abbr, int amount, float price) {
    /* WRITE YOUR CODE HERE */
}

void insert_sell_request(StockMarket *market, Person **people, int people_count, char *seller_name, char *company_abbr, int amount, float price) {
    /* WRITE YOUR CODE HERE */
}

void print_market(StockMarket *market) {
    /* WRITE YOUR CODE HERE */
}
