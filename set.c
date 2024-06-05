    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct Node
    {
        char data;
        struct Node *next;
    } Node;

    typedef struct set
    {
        int size;
        Node *head;
    } Set;

    void emptySet(Set *setsi);
    void printSet(Set *setsi);
    Node *createNode(char data);
    void initializeSet(Set *setsi);
    void sortSet(Set *setsi, int size);
    void addToSet(Set *setsi, char data);
    Set *unionOfSet(Set *setsi1, Set *setsi2);
    bool thereExists(Set *setsi, char noddieChar);
    Set *intersectionOfSet(Set *setsi1, Set *setsi2);
    Set *createSet(Set *setsi, char cadenita[], int size);

        int main(void)
    {

        char str1[101]; // El tamaño máximo es 101, dado que se pueden tener 50 caracteres, con 49 comas y 2 llaves.
        memset(str1, 0, sizeof(str1));
        scanf("%s", str1);

        char str2[101]; 
        memset(str2, 0, sizeof(str2));
        scanf("%s", str2);

        printf("\n");

        Set setsi1;
        initializeSet(&setsi1);
        createSet(&setsi1, str1, 101);
        printf("Set A: ");
        printSet(&setsi1);
        printf("\n");

        Set setsi2;
        initializeSet(&setsi2);
        createSet(&setsi2, str2, 101);
        printf("Set B: ");
        printSet(&setsi2);
        printf("\n");

        Set* union1;
        union1 = unionOfSet(&setsi1, &setsi2);
        printf("Set  A ∪ B: ");
        printSet(union1);
        printf("\n");

        Set *intersection1;
        intersection1 = intersectionOfSet(&setsi1, &setsi2);
        printf("Set  A ∩ B: ");
        printSet(intersection1);

        return 0;
    }

    void initializeSet(Set *setsi)
    {
        setsi->head = NULL;
        setsi->size = 0;
    }

    Node *createNode(char data)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = NULL;

        return newNode;
    }

    void addToSet(Set *setsi, char data)
    {
        Node *newNode = createNode(data);
        Node *passing = setsi->head;

        if (!thereExists(setsi, data))
        {
            if (setsi->head == NULL)
            {
                setsi->head = newNode;
            }
            else
            {
                while (passing->next != NULL)
                {
                    passing = passing->next;
                }

                passing->next = newNode;
            }
            setsi->size++;
        }
    }

    bool thereExists(Set *setsi, char noddieChar)
    {
        Node *passing = setsi->head;
        if (setsi->head == NULL)
        {
            return false;
        }
        while (passing->next != NULL)
        {
            if (passing->data == noddieChar)
            {
                return true;
            }

            passing = passing->next;
        }

        if (passing->data == noddieChar)
        {
            return true;
        }
        return false;
    }

    Set *createSet(Set *setsi, char cadenita[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            if (cadenita[i] != '\0' && cadenita[i] != '{' && cadenita[i] != '}' && cadenita[i] != ',')
            {
                addToSet(setsi, cadenita[i]);
            }
        }

        return setsi;
    }

    void printSet(Set *setsi)
    {
        sortSet(setsi, setsi->size);
        Node *passing = setsi->head;
        printf("{");
        while (passing != NULL)
        {
            if (passing->next == NULL)
            {
                printf("%c", passing->data);
            }
            else
            {
                printf("%c,", passing->data);
            }
            passing = passing->next;
        }
        printf("}\n");
    }

    void emptySet(Set *setsi)
    {
        Node *current = setsi->head;
        Node *next;

        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }

        setsi->head = NULL;
        setsi->size = 0;
    }

    void sortSet(Set *setsi, int size)
    {
        char temp = 0;
        char aux[size];
        Node *passing = setsi->head;
        memset(aux, '\0', sizeof(aux));

        for (int i = 0; i < size; i++)
        {
            aux[i] = passing->data;
            passing = passing->next;
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (aux[j] < aux[i])
                {
                    temp = aux[i];
                    aux[i] = aux[j];
                    aux[j] = temp;
                }
            }
        }

        emptySet(setsi);

        for (int i = 0; i < size; i++)
        {
            addToSet(setsi, aux[i]);
        }
    }

    Set *unionOfSet(Set *setsi1, Set *setsi2)
    {
        Set* unionSet = (Set*)malloc(sizeof(Set));
        initializeSet(unionSet);

        Node *passing1 = setsi1->head;
        while(passing1 != NULL){
            addToSet(unionSet, passing1->data);
            passing1 = passing1->next;
        }

        Node *passing2 = setsi2->head;
        while (passing2 != NULL)
        {
            addToSet(unionSet, passing2->data);
            passing2 = passing2->next;
        }

        return unionSet;
    }

    Set *intersectionOfSet(Set *setsi1, Set *setsi2)
    {
        Set *intersectionSet = (Set *)malloc(sizeof(Set));
        initializeSet(intersectionSet);

        Node *passing1 = setsi1->head;
        Node *passing2 = setsi2->head;

        while (passing1 != NULL)
        {
            Node *passing2 = setsi2->head;
            while (passing2 != NULL)
            {
                if (passing1->data == passing2->data)
                {
                    char dataIn = passing1->data;
                    addToSet(intersectionSet, dataIn);
                }
                passing2 = passing2->next;
            }
            passing1 = passing1->next;
        }

        return intersectionSet;
    }