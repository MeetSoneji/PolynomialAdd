#include <stdio.h>
#include <stdlib.h>
struct Term
{
    int coefficient;
    int exponentX;
    int exponentY;
    struct Term *next;
};
struct Term *createTerm(int coefficient, int exponentX, int exponentY)
{
    struct Term *newTerm = (struct Term *)malloc(sizeof(struct Term));
    if (newTerm == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newTerm->coefficient = coefficient;
    newTerm->exponentX = exponentX;
    newTerm->exponentY = exponentY;
    newTerm->next = NULL;
    return newTerm;
}
void insertTerm(struct Term **polynomial, int coefficient, int exponentX, int exponentY)
{
    struct Term *newTerm = createTerm(coefficient, exponentX, exponentY);
    if (*polynomial == NULL)
    {
        *polynomial = newTerm;
    }
    else
    {
        struct Term *temp = *polynomial;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newTerm;
    }
}
void displayPolynomial(struct Term *polynomial)
{
    if (polynomial == NULL)
    {
        printf("Polynomial is empty!\n");
        return;
    }
    struct Term *temp = polynomial;
    printf("Polynomial: ");
    while (temp != NULL)
    {
        printf("%d", temp->coefficient);
        if (temp->exponentX > 0)
        {
            printf("x^%d", temp->exponentX);
        }
        if (temp->exponentY > 0)
        {
            printf("y^%d", temp->exponentY);
        }
        if (temp->next != NULL)
        {
            printf(" + ");
        }
        temp = temp->next;
    }
    printf("\n");
}
struct Term *addPolynomials(struct Term *poly1, struct Term *poly2)
{
    struct Term *result = NULL;

    while (poly1 != NULL && poly2 != NULL)
    {
        if (poly1->exponentX > poly2->exponentX || (poly1->exponentX == poly2->exponentX && poly1->exponentY > poly2->exponentY))
        {
            insertTerm(&result, poly1->coefficient, poly1->exponentX, poly1->exponentY);
            poly1 = poly1->next;
        }
        else if (poly1->exponentX < poly2->exponentX || (poly1->exponentX == poly2->exponentX && poly1->exponentY < poly2->exponentY))
        {
            insertTerm(&result, poly2->coefficient, poly2->exponentX, poly2->exponentY);
            poly2 = poly2->next;
        }
        else
        {
            int sum = poly1->coefficient + poly2->coefficient;
            if (sum != 0)
            {
                insertTerm(&result, sum, poly1->exponentX, poly1->exponentY);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL)
    {
        insertTerm(&result, poly1->coefficient, poly1->exponentX, poly1->exponentY);
        poly1 = poly1->next;
    }

    while (poly2 != NULL)
    {
        insertTerm(&result, poly2->coefficient, poly2->exponentX, poly2->exponentY);
        poly2 = poly2->next;
    }
    return result;
}
int main()
{
    struct Term *poly1 = NULL;
    struct Term *poly2 = NULL;
    insertTerm(&poly1, 3, 2, 3);
    insertTerm(&poly1, 2, 1, 4);
    insertTerm(&poly1, 1, 0, 0);
    insertTerm(&poly2, 2, 1, 4);
    insertTerm(&poly2, -1, 2, 3);
    insertTerm(&poly2, 5, 0, 2);
    printf("First ");
    displayPolynomial(poly1);
    printf("Second ");
    displayPolynomial(poly2);
    struct Term *result = addPolynomials(poly1, poly2);
    printf("Result ");
    displayPolynomial(result);
    return 0;
}
