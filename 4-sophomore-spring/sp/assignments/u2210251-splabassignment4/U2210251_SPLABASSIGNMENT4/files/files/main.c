#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct node {
    char id[9];
    int section;
    char name[30];
    char level[10];
    char email[30];
    char phone[15];
    char program[5];
    struct node *next;
} Node;

Node *createNode(const char *id, const char *name, int section, const char *program, const char *level, const char *email, const char *phone) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    printf("\tnew node: %s, %s, %d, %s, %s, %s, %s \n", id, name, section, program, level, email, phone);
    strcpy(newNode->id, id);
    strcpy(newNode->name, name);
    newNode->section = section;
    strcpy(newNode->program, program);
    strcpy(newNode->level, level);
    strcpy(newNode->email, email);
    strcpy(newNode->phone, phone);
    newNode->next = NULL;
    return newNode;
}

void deleteNode(Node *node) {
    printf("free(size: %ld) at %p:\n", sizeof(*node), node);
    printf("\tDeleting node : %s, %s, %d, %s, %s, %s, %s \n", node->id,  node->name,  node->section,  node->program,  node->level,  node->email,  node->phone);
    free(node);
}

int countLeaks(Node *head) {
    int count = 0;
    Node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void resolveMemoryLeaks(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next_node = current->next;
        deleteNode(current);
        current = next_node;
    }
}

Node* nodeCreator(int i){

    switch(i){
        case 2:
            return createNode("U2210086", "Inomjonov Javokhirbek", 3, "CSE", "SOPHOMORE", "j.inomjonov@student.inha.", "+998974430132");
            break;
        case 3:
            return createNode("U2210251", "Xatamov Javohirbek", 3, "CSE", "SOPHOMORE", "j.xatamov@student.inha.uz", "+998902075639");
        break;
        case 4:
            return createNode("U2210050", "Bazarov Sarvar", 1, "ICE", "SOPHOMORE", "s.bazarov@student.inha.uz", "+998977244429");
            break;
        case 5:
            return createNode("U2210002", "Abdimannabov Sardor", 2, "CSE", "SOPHOMORE", "s.abdimannabov@student.inha.uz", "+998931857667");
            break;
        case 6:
            return createNode("U2210131", "Makhmudov Sardor", 1, "ICE", "SOPHOMORE", "s.makhmudov@student.inha.uz", "+998990202235");
            break;
        case 7:
            return createNode("U2210025", "Akramov Rashod", 1, "ICE", "SOPHOMORE", "r.akramov@student.inha.uz", "+998909162868");
            break;
        case 8:
            return createNode("U2210206", "Saydaxmedov Sayidaxror", 1, "ICE", "SOPHOMORE", "s.saydaxmedov@student.inha.uz", "+998946991483");
            break;
        case 9:
            return createNode("U2210184", "Rakhmanova Kamila", 4, "CSE", "SOPHOMORE", "k.rakhmanova@student.inha.uz", "+998935647453");
            break;
        case 10:
            return createNode("U2210138", "Maxkamov Abbos", 4, "CSE", "SOPHOMORE", "a.maxmakov@student.inha.uz", "+998909645070");
            break;
        case 11:
            return createNode("U2210051", "Begmamatova Muattar", 2, "CSE", "SOPHOMORE", "m.begmamatova@student.inha.uz", "+998934630410");
            break;
        case 12:
            return createNode("U2210122", "Shovkatjon Komilov", 3, "CSE", "SOPHOMORE", "s.komilov3@student.inha.uz", "+998990515405");
            break;
        case 13:
            return createNode("U2210151", "Muhammadov Maxmudjon", 1, "ICE", "SOPHOMORE", "m.muhammadov@student.inha.uz", "+998901191618");
            break;
        case 14:
            return createNode("U2210008", "Nodirakhon Abdullaeva", 2, "CSE", "SOPHOMORE", "n.abdullaeva@student.inha.uz", "+998884752020");
            break;
        case 15:
            return createNode("U2210085", "Ilyosov Doniyor", 2, "CSE", "SOPHOMORE", "d.ilyosov@student.inha.uz", "+998990252005");
            break;
        case 16:
            return createNode("U2210229", "Tulkunov Xasan", 4, "CSE", "SOPHOMORE", "x.tulkunov@student.inha.uz", "+998908944442");
            break;
        case 17:
            return createNode("U2210096", "Jorayev Saidakbar", 4, "CSE", "SOPHOMORE", "s.jo'rayev@student.inha.uz", "+998909262968");
            break;
        case 18:
            return createNode("U2210172", "O’ktamjonova Farangis", 4, "CSE", "SOPHOMORE", "f.ôktamjonova@student.inha.uz", "+998935716615");
            break;
        case 19:
            return createNode("U2210249", "Xalibayev Iskander", 4, "CSE", "SOPHOMORE", "i.xalibayev@student.inha.uz", "+998936969228");
            break;
        case 20:
            return createNode("U2210233", "Tursunov Asiliddin", 4, "CSE", "SOPHOMORE", "a.tursunov4@student.inha.uz", "+998903737713");
        break;
        case 21:
            return createNode("U2210278", "Musulmonov Abror", 4, "CSE", "SOPHOMORE", "a.musulmonov@student.inha.uz", "+998 93 443 60 04");
            break;
        case 22:
            return createNode("U2210253", "Xonboboyev Abdulxafizxon", 3, "CSE", "SOPHOMORE", "a.xonboboyev@student.inha.uz", "+998907885003");
            break;
        case 23:
            return createNode("U2210203", "Saidova Jasmina", 3, "CSE", "SOPHOMORE", "j.saidova@student.inha.uz", "+998974104024");
            break;
        case 24:
            return createNode("U2210214", "Sodikov Akmaljon", 3, "CSE", "SOPHOMORE", "a.sodikov3@student.inha.uz", "+998900941289");
            break;
        case 25:
            return createNode("U2210077", "Gayday Aleksey", 2, "CSE", "SOPHOMORE", "a.gayday@student.inha.uz", "+998914320516");
            break;
        case 26:
            return createNode("U2210134", "Mansurov Diyorbek", 3, "CSE", "SOPHOMORE", "d.mansurov@student.inha.uz", "+998908297743");
            break;
        case 27:
            return createNode("U2210112", "Kim Aleksandr", 1, "ICE", "SOPHOMORE", "a.kim7@student.inha.uz ", "+998915395545");
            break;
        case 28:
            return createNode("U2210125", "Temur Kuchkarov", 1, "ICE", "SOPHOMORE", "t.kuchkarov@student.inha.uz", "973339033");
            break;
        case 29:
            return createNode("U2210227", "Tselishcheva Milana", 3, "CSE", "SOPHOMORE", "m.tselishcheva@student.inha.uz", "+998909555369");
            break;
        case 30:
            return createNode("U2210246", "Vosiljonov Mirvokhid", 4, "CSE", "SOPHOMORE", "m.vosiljonov@student.inha.uz", "+998930084603");
            break;
        case 31:
            return createNode("U2210116", "Kim Denis ", 1, "ICE", "SOPHOMORE", "d.kim5@student.inha.uz ", "+998339154327");
            break;
        case 32:
            return createNode("U2210183", "Rakhmanov Azizjon", 1, "ICE", "SOPHOMORE", "a.rakhmanov@student.inha.uz", "+998330019896");
            break;
        case 33:
            return createNode("U2210167", "Nurmuhammad Nuriddinov", 1, "ICE", "SOPHOMORE", "n.nuriddinov@student.inha.uz", "+998996640849");
            break;
        case 34:
            return createNode("U2210219", "Tayirova Norjonoy", 3, "CSE", "SOPHOMORE", "n.tayirova@student.inha.uz", "+998934347628");
            break;
        case 35:
            return createNode("U2210217", "Sultanov Amal", 4, "CSE", "SOPHOMORE", "a.sultanov2@student.inha.uz", "+998935960748");
            break;
        case 36:
            return createNode("U2210171", "Muslima Okiljonova", 1, "ICE", "SOPHOMORE", "m.okiljonova@student.inha.uz", "+998940263373");
            break;
        case 37:
            return createNode("U2210207", "Sharipova Nargiza", 3, "CSE", "SOPHOMORE", "n.sharipova@student.inha.uz", "+998907116702");
            break;
        case 38:
            return createNode("U2210108", "Khegay Viktor", 3, "CSE", "SOPHOMORE", "v.khegay@student.inha.uz", "+998900335569");
            break;
        case 39:
            return createNode("U2210231", "Turayev Abdugafur", 4, "CSE", "SOPHOMORE", "a.turayev@student.inha.uz", "+998998689445");
            break;
        case 40:
            return createNode("U2210204", "Samokhin Kirill", 3, "CSE", "SOPHOMORE", "k.samokhin@student.inha.uz", "+998909391435");
            break;
        case 41:
            return createNode("U2210084", "Ilkhomov Farrukh", 1, "ICE", "SOPHOMORE", "f.ilkhomov@student.inha.uz", "+998903279011");
            break;
        case 42:
            return createNode("U2210141", "Maxmudov Komron", 1, "ICE", "SOPHOMORE", "kamranmaxmudov9@gmail.com", "+998915422734");
            break;
        case 43:
            return createNode("U2210117", "Kim Svetlana", 1, "ICE", "SOPHOMORE", "cydnsa.ks@gmail.com", "+998998661678");
            break;
        case 44:
            return createNode("U2210239", "Urazbaev Nurmukhamed", 4, "CSE", "SOPHOMORE", "n.urazbaev@student.inha.uz", "+998930025154");
            break;
        case 45:
            return createNode("U2210083", "Ilchikayev Amir", 1, "ICE", "SOPHOMORE", "a.ilchikayev@student.inha.uz ", "+998909956027");
            break;
        case 46:
            return createNode("U2210018", "Ablyayeva Susanna", 2, "CSE", "SOPHOMORE", "s.ablyayeva@student.inha.uz", "+998911375550");
            break;
        case 47:
            return createNode("U2210011", "Zeboxon Abdullayeva", 4, "CSE", "SOPHOMORE", "z.abdullayeva@student.inha.uz", "+998901234567");
            break;
        case 48:
            return createNode("U2210259", "Yuldoshaliev Shakhriyor", 4, "CSE", "SOPHOMORE", "s.yuldoshaliev@student.inha.uz", "+998946111707");
            break;
        case 49:
            return createNode("U2210024", "Akhrarova Munisa ", 2, "CSE", "SOPHOMORE", "m.akhrarova@student.inha.uz", "+998935820811");
            break;
        case 50:
            return createNode("U2210234", "Uyg’un Tursunov", 4, "CSE", "SOPHOMORE", "u.tursunov@student.inha.uz", "+998912445105");
            break;
        case 51:
            return createNode("U2210279", "Islomov Kamronbek", 4, "CSE", "SOPHOMORE", "k.islomov@student.inha.uz", "+998902965156");
            break;
        case 52:
            return createNode("U2210187", "Javohir Rasuljanov", 4, "CSE", "SOPHOMORE", "j.rasuljonov@student.inha.uz", "+998998652057");
            break;
        case 53:
            return createNode("U2210142", "Maxsudov Mirshod", 1, "ICE", "SOPHOMORE", "mirshodmakhsudov@gmail.com", "+998334009697");
            break;
        case 54:
            return createNode("U2210031", "Anvarov  Aslbek", 2, "CSE", "SOPHOMORE", "a.anvarov2@student.inha.uz", "+998901883599");
            break;
        case 55:
            return createNode("U2210033", "Arslonov Zokirjon", 2, "CSE", "SOPHOMORE", "z.arslonov@student.inha.uz", "+998996418060");
            break;
        case 56:
            return createNode("U2210028", "Alokhujaev Akbarkhuja", 3, "CSE", "SOPHOMORE", "a.alokhujaev@student.inha.uz", "+998990493336");
            break;
        case 57:
            return createNode("U2210226", "To'ychiyeva Nozima", 3, "CSE", "SOPHOMORE", "n.to'ychiyeva@student.inha.uz", "+998 99 879 90 28");
            break;
        case 58:
            return createNode("U2210064", "Ergashev Muhammadaziz", 1, "ICE", "SOPHOMORE", "m.ergashev@student.inha.uz", "+998974212004");
            break;
        case 59:
            return createNode("U2210061", "Dyugay Vladimir", 1, "ICE", "SOPHOMORE", "v.dyugay@student.inha.uz", "+998901342108");
            break;
        case 60:
            return createNode("U2210082", "Ibroilov Izzatulla", 1, "ICE", "SOPHOMORE", "iibroilov@gmail.com", "+998908225808");
            break;
        case 61:
            return createNode("U2210244", "Valiev Mustafo", 3, "CSE", "SOPHOMORE", "m.valiyev@student.inha.uz", "+998906553072");
            break;
        case 62:
            return createNode("U2210094", "Jo’raqulov Anvarjon", 1, "ICE", "SOPHOMORE", "anvarjonjurakulov@gmail.com", "+998999999056");
            break;
        default:
            return createNode("U2210130", "Makhmudov Imronbek", 4, "CSE", "SOPHOMORE", "i.makhmudov@student.inha.uz", "+998771779775");
}
}
int randNumGenerator(int arr[]){
    unsigned int randval;
    int label = 1;
    while(label){
        
        FILE *f;
        f = fopen("/dev/random", "r");
        fread(&randval, sizeof(randval), 1, f);
        fclose(f);
        randval %=60;
        if(randval == 0){continue;}
        for(int i = 0; i < 60; i++){
            if(arr[i] == randval){
                break;
            }
            if(arr[i] == 0){
                arr[i] = randval;
                label = 0;
                break;
            }
        } 
    }
    return randval;
}
int main() {
    int arr[60];
    int n, m;
    int randNum;
    for(int i = 0; i < 60; i++){
        arr[i] = 0;
    }
    printf("Enter the number of nodes (n): ");
    scanf("%d", &n);
    printf("Enter the number of nodes to delete (m): ");
    scanf("%d", &m);

    printf ("------------------------MALLOC------------------------\n");
    randNum = randNumGenerator(arr);
    Node *head = nodeCreator(randNum);
    Node *current = head;
    for (int i = 2; i <= n; i++) {
        randNum = randNumGenerator(arr);
        current->next = nodeCreator(randNum);
        current = current->next;
    }
    printf ("------------------------FREE------------------------\n");
    current = head;
    for (int i = 1; i <= m; i++) {
        Node *next_node = current->next;
        deleteNode(current);
        current = next_node;
    }
    printf ("------------------------MEMORY LEAKS-------------------- \n");
    int leaks = countLeaks(current);
    printf("\nMemory leaks detected: %d\n", leaks);

    resolveMemoryLeaks(current);

    return 0;
}

