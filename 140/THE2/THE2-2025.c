#include "stock_market.h"

Person* create_person(char *name, int id) 
{
    Person *newPerson;

    if (name == NULL)
        return NULL; 
    newPerson = (Person*)malloc(sizeof(Person)); 

    if (newPerson == NULL)
        return NULL; 

    newPerson->id = id;
    strcpy(newPerson->name, name); 

    return newPerson; 
}

Company* create_company(char *name, char *abbr, int order) 
{
    Company *newCompany = (Company*)malloc(sizeof(Company)); 

    if (name == NULL || abbr == NULL)
        return NULL; 
 
    if (!newCompany)
        return NULL; 
    
    newCompany->market_order = order; 
    strcpy(newCompany->name, name); 

    strcpy(newCompany->stock_abbreviation, abbr); 

    return newCompany; 
}

void add_company_to_market(StockMarket *market, Company *company) 
{
    if (market && company)
    { 
        market->entries[market->company_count].company = company;
        market->entries[market->company_count].buy_requests = NULL;
        market->entries[market->company_count].sell_requests = NULL; 
        market->company_count += 1; 
    }
}

RequestNode* create_request_node(Person *p, int amount, float price) 
{
    RequestNode *newNode; 
    Request newRequest; 
    if (!p)
        return NULL; 


    newNode = (RequestNode*)malloc(sizeof(RequestNode)); 

    if (!newNode)
        return NULL; 
    
    newRequest.amount = amount; 
    newRequest.price_per_share = price; 
    newRequest.person = p; 

    newNode->data = newRequest; 
    newNode->next = NULL; 

    return newNode; 
}

void insert_sorted(RequestNode **head, RequestNode *node, int ascending)
{
    RequestNode *current, *prev; 
    if (node != NULL)
    {   
        if (*head == NULL) {
            *head = node;
            return; 
        }

        current = *head, prev = NULL;

        if (ascending) 
        {
            while (current != NULL && node->data.price_per_share >= current->data.price_per_share) {
                prev = current;
                current = current->next;
            }
        } 
        else 
        {
            while (current != NULL && node->data.price_per_share <= current->data.price_per_share) {
                prev = current;
                current = current->next;
            }
        }

        node->next = current;

        if (prev == NULL)
            *head = node;
        else
            prev->next = node;
    }
}


void insert_buy_request(StockMarket *market, Person **people, int people_count, char *buyer_name, char *company_abbr, int amount, float price) 
{
    if (market != NULL && *people != NULL && company_abbr != NULL)
    {
        int i,j; 
        Person *buyer = NULL;
        StockMarketEntry *companyEntry = NULL; 
        RequestNode *current, *prev = NULL;  

        for (i = 0; i<people_count; i++)
        {
            if (strcmp(people[i]->name, buyer_name) == 0)
            {
                buyer = people[i]; 
            }
        }


        for (j = 0; j<market->company_count; j++)
        {
            if (strcmp(market->entries[j].company->stock_abbreviation, company_abbr) == 0)
            {
                companyEntry = &market->entries[j]; 
            }
        }


        current = companyEntry->sell_requests;
        prev = NULL;

        while (current != NULL && amount > 0) 
        {
            if (current->data.price_per_share <= price)
            {
                if (amount == current->data.amount)
                {
                    int tradeAmount = amount; 
                    RequestNode *tempCurrent = current;
                    if (current->data.person == NULL && buyer_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, "(null)", "(null)");
                    }
                    else if (current->data.person != NULL && buyer_name != NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, current->data.person->name, buyer_name);
                    }
                    else if (current->data.person != NULL && buyer_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, current->data.person->name, "(null)");
                    }
                    else 
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, "(null)", buyer_name);
                    }

                    amount = 0; 
                    current->data.amount = 0; 

                    current = current->next;

                    if (prev == NULL)
                        companyEntry->sell_requests = current;
                    else
                        prev->next = current;

                    free(tempCurrent);  

                }
                else if (amount > current->data.amount)
                {
                    RequestNode *tempCurrent = current;
                    int tradeAmount = current->data.amount; 

                    if (current->data.person == NULL && buyer_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, "(null)", "(null)");
                    }
                    else if (current->data.person != NULL && buyer_name != NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, current->data.person->name, buyer_name);
                    }
                    else if (current->data.person != NULL && buyer_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, current->data.person->name, "(null)");
                    }
                    else 
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, "(null)", buyer_name);
                    }
                    amount -= tradeAmount; 
                    current->data.amount = 0; 
                    current = current->next;

                    if (prev == NULL)
                        companyEntry->sell_requests = current;
                    else
                        prev->next = current;

                    free(tempCurrent);  
                }
                else 
                {
                    int tradeAmount = amount; 
                    if (current->data.person == NULL && buyer_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, "(null)", "(null)");
                    }
                    else if (current->data.person != NULL && buyer_name != NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, current->data.person->name, buyer_name);
                    }
                    else if (current->data.person != NULL && buyer_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, current->data.person->name, "(null)");
                    }
                    else 
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, current->data.price_per_share, "(null)", buyer_name);
                    }  
                    current->data.amount -= tradeAmount;   
                    amount = 0;   
                    
                    prev = current; 
                    current = current->next; 
                    }
                }
            else 
            {
                prev = current;
                current = current->next;
            }
        }

        if (amount > 0)
        {
            RequestNode *newNode = create_request_node(buyer, amount, price); 
            if (newNode)
                insert_sorted(&companyEntry->buy_requests, newNode, 0); 
        }
    }
}

void insert_sell_request(StockMarket *market, Person **people, int people_count, char *seller_name, char *company_abbr, int amount, float price) 
{
    if (market != NULL && *people != NULL && company_abbr != NULL)
    {
        int i,j; 
        Person *seller = NULL;
        StockMarketEntry *companyEntry = NULL; 
        RequestNode *current, *prev = NULL;  

        for (i = 0; i<people_count; i++)
        {
            if (strcmp(people[i]->name, seller_name) == 0)
            {
                seller = people[i]; 
            }
        }


        for (j = 0; j<market->company_count; j++)
        {
            if (strcmp(market->entries[j].company->stock_abbreviation, company_abbr) == 0)
            {
                companyEntry = &market->entries[j]; 
            }
        }


        current = companyEntry->buy_requests;
        prev = NULL;

        while (current != NULL && amount > 0) 
        {
            if (current->data.price_per_share >= price)
            {
                if (amount == current->data.amount)
                {
                    RequestNode *tempCurrent = current;
                    int tradeAmount = amount; 
                    if (current->data.person== NULL && seller_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n",tradeAmount, companyEntry->company->stock_abbreviation, price, "(null)", "(null)");
                    }
                    else if (current->data.person != NULL && seller_name != NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price, seller_name,current->data.person->name);
                    }
                    else if (current->data.person != NULL && seller_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price, "(null)",current->data.person->name);
                    }
                    else 
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price,seller_name ,"(null)");
                    }

                    amount = 0; 
                    current->data.amount = 0; 

                    current = current->next;

                    if (prev == NULL)
                        companyEntry->buy_requests = current;
                    else
                        prev->next = current;

                    free(tempCurrent);  

                }
                else if (amount > current->data.amount)
                {
                    RequestNode *tempCurrent = current;
                    int tradeAmount = current->data.amount; 

                    if (current->data.person== NULL && seller_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price, "(null)", "(null)");
                    }
                    else if (current->data.person != NULL && seller_name != NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price, seller_name,current->data.person->name);
                    }
                    else if (current->data.person != NULL && seller_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price, "(null)",current->data.person->name);
                    }
                    else 
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price,seller_name ,"(null)");
                    }
                    amount = amount - tradeAmount; 
                    current->data.amount = 0; 
                    current = current->next;

                    if (prev == NULL)
                        companyEntry->buy_requests = current;
                    else
                        prev->next = current;

                    free(tempCurrent);  
                }
                else 
                {
                    int tradeAmount = amount; 
                    if (current->data.person== NULL && seller_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price, "(null)", "(null)");
                    }
                    else if (current->data.person != NULL && seller_name != NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price, seller_name,current->data.person->name);
                    }
                    else if (current->data.person != NULL && seller_name == NULL)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price, "(null)",current->data.person->name);
                    }
                    else 
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", tradeAmount, companyEntry->company->stock_abbreviation, price,seller_name ,"(null)");
                    }
                    current->data.amount -= tradeAmount;     
                    amount = 0; 
                                        
                    prev = current; 
                    current = current->next; 
                    }
                }
            else 
            {
                prev = current;
                current = current->next;
            }
        }

        if (amount > 0)
        {
            RequestNode *newNode = create_request_node(seller, amount, price); 
            if (newNode)
                insert_sorted(&companyEntry->sell_requests, newNode, 1); 
        }
    }
}

void print_market(StockMarket *market) 
{
    
    if (market != NULL)
    {
        int count = market->company_count; 
        int i; 
        for (i = 0; i < count; i++) {
            StockMarketEntry *entry = &market->entries[i];
            Company *company = entry->company;
            RequestNode *currentBuy = entry->buy_requests;
            RequestNode *currentSell = entry->sell_requests;


            printf("Company: %s (%s)\n", company->name, company->stock_abbreviation);

            printf("\tBuy Requests:\n");

            while (currentBuy != NULL && currentBuy->data.amount > 0) 
            {
                printf("\t\t%s wants %d @ %.2f\n", currentBuy->data.person->name, currentBuy->data.amount, currentBuy->data.price_per_share);
                currentBuy = currentBuy->next;
            }

            printf("\tSell Requests:\n");

            while (currentSell != NULL && currentSell->data.amount > 0) 
            {
                printf("\t\t%s sells %d @ %.2f\n",currentSell->data.person->name, currentSell->data.amount, currentSell->data.price_per_share);
                currentSell = currentSell->next;
            }
        }
    }
}

