#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ARTICLE_NAME (128)
#define MAX_LINE (1024)

struct _article;
typedef struct _article* ArticleP;
typedef struct _article {
    char name[MAX_ARTICLE_NAME];
    int price;
    ArticleP next;
} Article;

struct _category;
typedef struct _category* CategoryP;
typedef struct _category {
    char name[MAX_ARTICLE_NAME];
    int minPrice;
    int maxPrice;
    float averagePrice;
    CategoryP next;
    ArticleP child;
} Category;

CategoryP CreateCategory();
ArticleP CreateArticle();
int InitializeCategory(CategoryP category);
int InitializeArticle(ArticleP article);
int ReadCategoriesFromFile(CategoryP head, char* categoryFileName);
int InsertCategorySorted(CategoryP head, CategoryP category);
int InsertCategoryAfter(CategoryP position, CategoryP category);
int InsertArticleAfter(ArticleP position, ArticleP article);
int InsertArticleSorted(ArticleP head, ArticleP article);
int PrintCategory(CategoryP first);
int PrintArticles(ArticleP first);
int DeleteAll(CategoryP head);
int main() {
    Category head;
    int status = 0;

    srand(time(NULL));

    InitializeCategory(&head);

    status = ReadCategoriesFromFile(&head, "kategorije.txt");
    status = ReadArticlesFromFile(&head, "proizvodi.txt");
    
    if (status != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    PrintCategory(head.next);
    DeleteAll(&head);

    return EXIT_SUCCESS;
}

int GenerateRandomPrice(int minPrice, int maxPrice)
{
    int randomNumber = 0;
    randomNumber = rand() % (maxPrice - minPrice + 1) + minPrice;

    return randomNumber;
}

CategoryP CreateCategory()
{
    CategoryP newCategory = NULL;

    newCategory = (CategoryP)malloc(sizeof(Category));
    if (!newCategory)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    InitializeCategory(newCategory);

    return newCategory;
}

ArticleP CreateArticle()
{
    ArticleP newArticle = NULL;

    newArticle = (ArticleP)malloc(sizeof(Article));
    if (!newArticle)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    InitializeArticle(newArticle);

    return newArticle;
}

int InitializeCategory(CategoryP category) {
    category->minPrice = 0;
    category->maxPrice = 0;
    category->averagePrice = 0;
    category->next = NULL;
    memset(category->name, 0, MAX_ARTICLE_NAME);
    category->child = CreateArticle();
    if (category->child == NULL)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int InitializeArticle(ArticleP article) {
    article->price = 0;
    memset(article->name, 0, MAX_ARTICLE_NAME);
    article->next = NULL;

    return EXIT_SUCCESS;
}

int ReadCategoriesFromFile(CategoryP head, char* categoryFileName) {
    FILE* fp = NULL;
    int status = EXIT_SUCCESS;

    fp = fopen(categoryFileName, "r");
    if (!fp) {
        perror("Category file not opened!");
        return EXIT_FAILURE;
    }

   
    while (!feof(fp)) {
        CategoryP category = NULL;
        category = CreateCategory();
        if (!category)
        {
            fclose(fp);
            return EXIT_FAILURE;
        }
        fscanf(fp, "%s %d %d", category->name, &category->minPrice, &category->maxPrice);

        InsertCategorySorted(head, category);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int ReadArticlesFromFile(CategoryP head, char* articleFileName) {
    FILE* fp = NULL;
    int status = EXIT_SUCCESS;
    char category[MAX_ARTICLE_NAME] = { 0 };
    CategoryP temp = head;
    int randomPrice = 0;

    fp = fopen(articleFileName, "r");
    if (!fp) {
        perror("Category file not opened!");
        return EXIT_FAILURE;
    }


    while (!feof(fp)) {
        ArticleP article = NULL;
        article = CreateArticle();
        if (!article)
        {
            fclose(fp);
            return EXIT_FAILURE;
        }
        fscanf(fp, "%s %s", article->name, category);
        while (temp->next != NULL && strcmp(temp->name, category) != 0) {
            temp = temp->next;
        }

        randomPrice = GenerateRandomPrice(temp->minPrice, temp->maxPrice);
      
        article->price = randomPrice;
        InsertArticleSorted(temp->child, article);
        temp = head;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int InsertCategorySorted(CategoryP head, CategoryP category) {
    CategoryP position = head;

    while (position->next != NULL && strcmp(position->next->name, category->name) < 0) {
        position = position->next;
    }

    InsertCategoryAfter(position, category);

    return EXIT_SUCCESS;
}

int InsertCategoryAfter(CategoryP position, CategoryP category) {
    category->next = position->next;
    position->next = category;

    return EXIT_SUCCESS;
}

int PrintCategory(CategoryP first)
{
    CategoryP temp = first;

    while (temp)
    {
        printf("%s\n", temp->name);
        PrintArticles(temp->child->next);
        printf("\n");
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

int PrintArticles(ArticleP first)
{
    ArticleP temp = first;

    while (temp)
    {
        printf("%s %d\n", temp->name, temp->price);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

int InsertArticleSorted(ArticleP head, ArticleP article) {
    ArticleP position = head;

    while (position->next != NULL && strcmp(position->next->name, article->name) < 0) {
        position = position->next;
    }

    InsertArticleAfter(position, article);

    return EXIT_SUCCESS;
}

int InsertArticleAfter(ArticleP position, ArticleP article) {
    article->next = position->next;
    position->next = article;

    return EXIT_SUCCESS;
}

int DeleteAll(CategoryP head)
{
    CategoryP tempCategory = NULL;
    ArticleP tempArticle = NULL;
    while (head->next != NULL)
    {
        while (head->next->child->next != NULL)
        {
            tempArticle = head->next->child->next;
            head->next->child->next = tempArticle->next;
            free(tempArticle);
        }

        tempCategory = head->next;
        head->next = tempCategory->next;
        free(tempCategory);
    }

    return EXIT_SUCCESS;
}