#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h> 

/*
    Kompiang Gede Sukadharma
    Informatika, Universias Udayana
    NIM: 2008561083
*/

// Function init berguna untuk mengassign bilangan sebanyak variabel longOfAssignedArray sesuai dengan
// metode yang berada di dalam variabel NorP
void init(int longOfAssignedArray, char NorP, int* arrayInit, int* unsortedArray);

// Function isPrime berfungsi untuk mengecek apakah bilangan random yang terdapat pada variabel randomNum
// merupakan bilangan prima atau bukan. Apabila bilangan tersebut adalah prima, akan mengembalikan nilai 1.
// Jika bukan, akan mengembalikan nilai 0
int isPrime(int randomNum);

// printArray berguna untuk memunculkan array ke layar dan juga menuliskan nilai output tersebut
// ke dalam file yang nama serta lokasinya terdapat dalam variabel pointer pointerToFile
void printArray (int* array, int longOfAssignedArray, FILE* pointerToFile);

// Function swap berguna untuk menukar nilai antara number1 dan number2
void swap (int* number1, int* number2);

// Function sort berguna untuk melakukan pengurutan sesuatu dengan pilUrut yaitu ascending atau descending
// serta pilSorting dari no 1-3, di mana masing-masing pilSorting memiliki algoritma yang berbeda-beda
void sort(int* array, int longOfAssignedArray, char* pilUrut, int pilSorting);

// Function search memiliki fungsi yaitu untuk melakukan pencarian angka dengan algoritma binary search
// Apabila angka tersebut ketemu, fungsi ini akan mengembalikan nilai 1. Apabila tidak, fungsi ini
// akan mengembalikan nilai 0
//
// NOTE: fungsi ini dapat digunakan ketika array sudah diurutkan. Jadi, gunakan function sort sebelum function ini
//
int search (int* array, int numberToFind, char* pilUrut, int longOfAssignedArray, int* findedNumberIndex);

// Function ini berfungsi untuk menyelipkan sebuah angka sesuai dengan urutannya. Jadi untuk menggunakan
// function ini, array yang kita miliki sudah harus terurut. Apabila kita berhasil menyelipkan nilai tersebut
// function ini akan mengemablikan nilai 1. Namun, apabila sebelum perintah ini dipanggil
// jumlah array yang terisi oleh angka random sudah 20, function ini akan mengemablikan nilai 0
//
// NOTE: fungsi ini dapat digunakan ketika array sudah diurutkan, jadi gunakan function sort sebelum function ini
//
int insert (int* array, int numbertoInsert, char* pilUrut, int* longOfAssignedArray);

int main(){
    char* token;
    char NorP, pilUrut[10], tempStringInput[60], stringInput[20], buffer[26];
    int longOfAssignedArray, unsortedArray[20], array[20], pilSorting, pilihanMenu, numberToFind;
    int numberToInsert, beforeUpdate, afterUpdate, findedNumberIndex;
    int numberToDelete, tryToCreateFile = 1;
    
    time_t timer;
    struct tm* tm_info;
    
    FILE* pointerToFile;

    puts("");
    puts("   Kompiang Gede Sukadharma   ");
    puts("          2008561083          ");

    while (1) {
        int sum = 0, tempIndexLoop = 0, manyEvenOrOddNumber = 0, loopForRenoveComma = 0;

        printf("\n##############################\n");                         
        puts("####### UAS Alpro 2020 #######");
        puts("# Pilih di antara angka 1-14 #");
        puts("##############################");
        printf("1. Init\t\t8. Min\n");
        printf("2. Sort\t\t9. Max\n");
        printf("3. Search\t10. Average\n");
        printf("4. Insert\t11. Ganjil\n");
        printf("5. Update\t12. Genap\n");
        printf("6. Delete\t13. Exit & Saved\n");
        printf("7. Count\t14. Exit Without Save\n");
        printf("Masukkan pilihan : "); scanf("%d", &pilihanMenu); getchar();
        puts("");

        switch (pilihanMenu){
            case 1:
                //Menmbuat file otomatis sesuai waktu saat dieksekusi hanya sekali
                if (tryToCreateFile == 1) {
                        timer = time(NULL);
                        tm_info = localtime(&timer);

                        // Mengassign waktu saat dieksekusi ke variabel buffer
                        strftime(buffer, 26, "%Y%m%d_%H%M%S.txt", tm_info);
                        // Membuat atau membuka file dengan nama yang ada di dalem buffer
                        // serta dengan mode a
                        pointerToFile = fopen(buffer, "a");
                        // Melakukan increment pada variabel tryToCreateFile agar perintah
                        // untuk menghitung waktu serta membuat file tidak tereksekusi
                        // berkali-kali
                        tryToCreateFile++;
                }

                // User harus menginputkan parameter dari init (n, metode)
                // Keterangan parameter
                /*
                    * n adalah banyak angka random yang diinginkan
                      banyak bilangan n tidak boleh lebih dari 20
                      dan tidak boleh kurang dari 0
                    * Metode yang ada adalah 
                        * n memasukkan semua bilangan random yang digenerate ke dalam array
                        * p memasukkan hanya bilangan random yang  prima ke dalam array
                */
                // Ketika user menginputkan bilangan leebih dari 20 atau kurang dari 0, serta
                // menginputkan char selain n atau p, maka program akan meminta input ulang
                // hingga user memasukkan input yang benar
                do {
                    printf ("input: init("); scanf ("%d, %c)", &longOfAssignedArray, &NorP);
                    fprintf (pointerToFile, "input: init("); fprintf (pointerToFile, "%d, %c)\n", longOfAssignedArray, NorP);
                    getchar ();      
                } while (! ((longOfAssignedArray >= 0 && longOfAssignedArray <= 20) && (NorP == 'n' || NorP == 'p')));


                puts("Output:");
                printf("Init:");

                fprintf(pointerToFile, "Output:\nInit:");
                
                init (longOfAssignedArray, NorP, array, unsortedArray);
                printArray (array, longOfAssignedArray, pointerToFile);
                fprintf (pointerToFile, "\n");
            continue;

            case 2:
                // User harus menginputkan parameter dari sort(array, pil_urut, pilihan_sorting)
                // Keterangan parameter
                /*
                    * array, tulisan ini ketik saja array pada terminal
                    * pil_urut
                      Masukkan salah satu, diikuti petik dua
                      * "asc", mengurutkan dari kecil ke besar
                      * "desc", mengurutkan 
                    * pilihan_sorting
                      Masukkan angka
                      1 untuk Bubble Sort; 2 untuk Selection Sort; 3 untuk Insertion Sort
                */
                // Ketika user menginputkan bilangan untuk parameter pil_urut kurang dari dan
                // lebih dari 3, serta menginputkan parameter pilihan_sorting selain "asc" dan "desc"
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do {
                    printf ("input: sort("); scanf ("%s", tempStringInput); getchar();
                    fprintf (pointerToFile, "input: sort("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    token = strtok (NULL,",");
                    strcpy (pilUrut, token);
                    token = strtok (NULL,",");
                    pilSorting = atoi (token);
                } while (! ( (pilSorting <= 3 && pilSorting >= 1) && (strcmp (pilUrut,"\"asc\"") == 0 || strcmp (pilUrut,"\"desc\"") ==0 ) ) );

                puts ("Output:");
                printf ("Array:");
                fprintf (pointerToFile, "Output:\nArray:");
                printArray (unsortedArray, longOfAssignedArray, pointerToFile);

                switch (pilSorting) {
                    case 1:
                        puts ("Metode: Bubble Sort");
                        fprintf (pointerToFile, "Metode: Bubble Sort\n");
                    break; 
                    
                    case 2:
                        puts ("Metode: Selection Sort");
                        fprintf (pointerToFile, "Metode: Selection Sort\n");
                    break;
                    
                    case 3:
                        puts ("Metode: Insertion Sort");
                        fprintf (pointerToFile, "Metode: Insertion Sort\n");
                    break;
                }

                printf ("Sort:");
                fprintf (pointerToFile, "Sort:");
                sort (array, longOfAssignedArray, pilUrut, pilSorting);
                printArray (array, longOfAssignedArray, pointerToFile);
                fprintf (pointerToFile, "\n");
            continue;

            case 3:
                // User harus menginputkan parameter dari search(n, array, pil_urut)
                // Keterangan parameter
                /*
                    * n, bilangan yang ingin dicari
                    * array, tulisan ini diketik saja array pada terminal
                    * pil_urut
                      Masukkan salah satu, diikuti petik dua
                      * "asc", mengurutkan dari kecil ke besar
                      * "desc", mengurutkan 
                */
                // Ketika user menginputkan parameter pilihan_sorting selain "asc" dan "desc"
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do {
                    printf ("input: search("); scanf ("%[^)]s", tempStringInput); getchar ();
                    fprintf (pointerToFile, "input: search("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    numberToFind = atoi (token);
                    token = strtok (NULL,",");
                    token = strtok (NULL,",");
                    strcpy (pilUrut,token);
                } while (! (strcmp(pilUrut,"\"asc\"") == 0 || strcmp (pilUrut,"\"desc\"") == 0) );

                printf ("Output:\nArray:");
                fprintf (pointerToFile, "Output:\nArray:");
                printArray (array, longOfAssignedArray, pointerToFile);
                
                sort (array, longOfAssignedArray, pilUrut, 1);
                printf ("Sort:");
                fprintf (pointerToFile, "Sort:");
                printArray (array, longOfAssignedArray, pointerToFile);
                
                printf ("Search: ");
                if (search (array, numberToFind, pilUrut, longOfAssignedArray, &findedNumberIndex) == 1) {
                    printf ("%d ditemukan pada indeks ke-%d", numberToFind, findedNumberIndex + 1);
                    fprintf (pointerToFile, "%d ditemukan pada indeks ke-%d", numberToFind, findedNumberIndex + 1);
                }
                else {
                    printf ("%d tidak ada dalam array", numberToFind);
                    fprintf (pointerToFile, "%d tidak ada dalam array", numberToFind);
                }
                printf("\n");
                fprintf (pointerToFile, "\n\n");
            continue;

            case 4:
                // User harus menginputkan parameter dari insert (n, pil_urut)
                // Keterangan parameter
                /*
                    * n, bilangan yang ingin diselipkan
                    * array, tulisan ini diketik saja array pada terminal
                    * pil_urut
                      Masukkan salah satu, diikuti petik dua
                      * "asc", mengurutkan dari kecil ke besar
                      * "desc", mengurutkan 
                */
                // Ketika user menginputkan parameter pilihan_sorting selain "asc" dan "desc"
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do {
                    printf ("input: insert("); scanf ("%[^)]s", tempStringInput); getchar ();
                    fprintf (pointerToFile, "input: insert("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    numberToInsert = atoi (token);
                    token = strtok (NULL,",");
                    strcpy (pilUrut,token);
                } while (! (strcmp(pilUrut,"\"asc\"") == 0 || strcmp (pilUrut,"\"desc\"") == 0));

                puts ("");
                puts ("Output");
                printf ("Array:");
                fprintf (pointerToFile, "Output:\nArray:");
                printArray (array, longOfAssignedArray, pointerToFile);
                
                printf ("Sort:");
                fprintf (pointerToFile, "Sort:");
                sort (array, longOfAssignedArray, pilUrut, 1);
                printArray (array, longOfAssignedArray, pointerToFile);

                printf ("Insert:");
                fprintf (pointerToFile, "Insert:");
                if (insert (array, numberToInsert, pilUrut, &longOfAssignedArray) == 1) {
                    printArray (array, longOfAssignedArray, pointerToFile);
                }
                else {
                    printf (" FULL - index out of bound founded\n");
                    fprintf (pointerToFile, " FULL - index out of bound founded\n");
                }

                fprintf (pointerToFile, "\n");
            continue;
                
            case 5:
                // Mode ini akan mengupate atau mengubah suatu bilangan n menjadi bilangan m
                // dan akan diurutkan kembali sesuai dengan pil_urut yang dipilih user
                // Namun, apabila bilangan n yang ingin diubah tidak ada, mode ini akan
                // meng-insert bilangan tersebut ke dalam array kemudian akan mengurutkan kembali

                // User harus menginputkan parameter dari update (n,m,pil_urut)
                // Keterangan parameter
                /*
                    * n, bilangan yang ingin diubah
                    * m, bilangan yang akan mengganti n
                    * pil_urut
                      Masukkan salah satu, diikuti petik dua
                      * "asc", mengurutkan dari kecil ke besar
                      * "desc", mengurutkan 
                */
                // Ketika user menginputkan parameter pilihan_sorting selain "asc" dan "desc"
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do {
                    printf ("input: update("); scanf ("%[^)]s", tempStringInput); getchar ();
                    fprintf (pointerToFile, "input: update("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    beforeUpdate = atoi (token);
                    token = strtok (NULL,",");
                    afterUpdate = atoi (token);
                    token = strtok (NULL,",");
                    strcpy (pilUrut,token);
                } while (! (strcmp (pilUrut,"\"asc\"") == 0 || strcmp (pilUrut,"\"desc\"") == 0));

                puts ("Output:");
                printf ("Array:");
                fprintf (pointerToFile, "Output:\nArray:");
                printArray (array, longOfAssignedArray, pointerToFile);
                sort (array, longOfAssignedArray, pilUrut, 1);
                printf ("Sorting:");
                fprintf (pointerToFile, "Sorting:");
                printArray (array, longOfAssignedArray, pointerToFile);

                // Kita memanfaat nilai yang dikembalikan oleh function search
                // * Apabila nilai yang dikembalikan 1, nilai tersebut akan diganti dengan nilai yang baru
                //
                // * Apabila nilai yang dikembalikan 0, mode ini akan mengeluarkan peringatan
                //   dan nilai tersebut akan dimasukkan ke dalam array dengan fungsi insert

                if (search (array, beforeUpdate, pilUrut, longOfAssignedArray, &findedNumberIndex) == 1) {
                    printf ("Update:");
                    fprintf (pointerToFile, "Update:");
                    array [findedNumberIndex] = afterUpdate;
                    sort  (array, longOfAssignedArray, pilUrut, 1);
                    printArray (array, longOfAssignedArray, pointerToFile);
                }
                else {
                    printf ("Update: Tidak ditemukan nilai %d\n", beforeUpdate);
                    fprintf (pointerToFile, "Update: Tidak ditemukan nilai %d\n", beforeUpdate);
                    printf ("Insert:");
                    fprintf (pointerToFile, "Insert:");
                    if (insert (array, beforeUpdate, pilUrut, &longOfAssignedArray) == 1) {
                        sort  (array, longOfAssignedArray, pilUrut, 1);
                        printArray (array, longOfAssignedArray, pointerToFile);
                     }
                    else {
                        printf (" FULL - index out of bound founded\n");
                        fprintf (pointerToFile, " FULL - index out of bound founded\n");
                    }
                }

                fprintf (pointerToFile, "\n");
            continue;

            case 6:
                // Mode ini akan menghapus suatu bilangan dari array terurut

                // User harus menginputkan parameter dari delete (n,pil_urut)
                // Keterangan parameter
                /*
                    * n, bilangan yang ingin dihapus
                    * pil_urut
                      Masukkan salah satu, diikuti petik dua
                      * "asc", mengurutkan dari kecil ke besar
                      * "desc", mengurutkan 
                */
                // Ketika user menginputkan parameter pilihan_sorting selain "asc" dan "desc"
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do {
                    printf ("input: delete("); scanf ("%[^)]s", tempStringInput); getchar ();
                    fprintf (pointerToFile, "input: delete("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    numberToDelete = atoi (token);
                    token = strtok (NULL,",");
                    strcpy (pilUrut,token);
                } while (! (strcmp (pilUrut,"\"asc\"") == 0 || strcmp (pilUrut,"\"desc\"") == 0));
                
                puts ("Output:");
                printf ("Array:");
                fprintf (pointerToFile, "Output:\nArray:");
                printArray (array, longOfAssignedArray, pointerToFile);
                
                printf ("Sorting:");
                fprintf (pointerToFile, "Sorting:");
                sort (array, longOfAssignedArray, pilUrut, 1);
                printArray (array, longOfAssignedArray, pointerToFile);

                // Kita memanfaat nilai yang dikembalikan oleh function search
                // * Apabila nilai yang dikembalikan 1, nilai tersebut akan dihapus.
                //   Secara teknik bilangan tersebut tidak dihapus. Namun, semua array yang
                //   disebelah kanan akan digeser satu persatu ke sebelah kiri untuk
                //   mengganti keberadaan bilangan yang ingin dihapus tersebut
                //
                // * Apabila nilai yang dikembalikan 0, mode ini akan mengeluarkan peringatan
                printf ("Delete:");
                fprintf (pointerToFile, "Delete:");
                if (search (array, numberToDelete, pilUrut, longOfAssignedArray, &findedNumberIndex) == 1) {
                    for (int i = findedNumberIndex ; i < longOfAssignedArray; i++) {
                        array [i] = array [i + 1];
                    }
                    longOfAssignedArray--;
                    printArray (array, longOfAssignedArray, pointerToFile);
                }
                else
                {
                    printf (" %d tidak ditemukan pada Array", numberToDelete);
                    fprintf (pointerToFile, " %d tidak ditemukan pada Array\n", numberToDelete);
                }

                fprintf (pointerToFile, "\n");
            continue;

            case 7:
                // Mode ini akan menghitung berapa bilangan yang memiliki nilai random

                // User harus menginputkan parameter dari count (array)
                // Keterangan parameter
                /*
                    * array, diketik saja pada terminal
                */
                // Ketika user menginputkan parameter pilihan_sorting selain array
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do{
                    printf ("input: count("); scanf ("%[^)]s", tempStringInput); getchar ();
                    fprintf (pointerToFile, "input: count("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    strcpy (stringInput,token);
                } while (! (strcmp (stringInput,"array") == 0));
                
                puts ("Output:");
                printf ("Array:");
                fprintf (pointerToFile, "Output:\nArray:");
                printArray (array, longOfAssignedArray, pointerToFile);

                // Memanfaatkan nilai dari variabel longOfAssignedArray
                // Karena variabel tersebut memiliki nilai dari banyaknya elemen array
                // yang telah dimasukkan nilai random
                printf ("Count: %d item\n\n", longOfAssignedArray);
                fprintf(pointerToFile, "Count: %d item\n\n", longOfAssignedArray);
            continue;

            case 8:
                // Mode ini akan mencari nilai terkecil pada array

                // User harus menginputkan parameter dari min (array) 
                // Keterangan parameter
                /*
                    * array, diketik saja pada terminal
                */
                // Ketika user menginputkan selain array
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do {
                    printf ("input: min("); scanf ("%[^)]s", tempStringInput); getchar ();
                    fprintf (pointerToFile, "input: min("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    strcpy (stringInput,token);
                } while (! (strcmp (stringInput,"array") == 0));

                puts ("Output:");
                printf ("Array:");
                fprintf(pointerToFile, "Output:\nArray:");
                printArray (array, longOfAssignedArray, pointerToFile);

                // Untuk mendapatkan nilai dari min kita dapat melakukan sorting dengan mode "Ascending"
                // atau mode dari terkecil ke terbesar. Kemudian, index pertama dari array pasti adalah
                // elemen yang paling kecil
                sort (array, longOfAssignedArray, "\"asc\"", 1);
                printf ("Min: %d\n", array[0]);
                fprintf (pointerToFile, "Min: %d\n", array[0]);

                fprintf (pointerToFile, "\n\n");
            continue;

            case 9:
                // Mode ini akan mencari dan menampilkan nilai terbesar pada array

                // User harus menginputkan parameter dari max (array) 
                // Keterangan parameter
                /*
                    * array, diketik saja pada terminal
                */
                // Ketika user menginputkan selain array
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do {
                    printf ("input: max("); scanf ("%[^)]s", tempStringInput); getchar ();
                    fprintf (pointerToFile, "input: max("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    strcpy (stringInput,token);
                } while (! (strcmp (stringInput,"array") == 0));

                puts ("Output:");
                printf ("Array:");
                fprintf (pointerToFile, "Output:\nArray:");
                printArray (array, longOfAssignedArray, pointerToFile);

                // Untuk mendapatkan nilai dari min kita dapat melakukan sorting dengan mode "Descending"
                // atau mode dari terbesar ke terkecil. Kemudian, index pertama dari array pasti adalah
                // elemen yang paling besar
                sort (array, longOfAssignedArray, "\"desc\"", 1);
                printf ("Max: %d\n", array[0]);
                fprintf (pointerToFile, "Max: %d\n", array[0]);

                fprintf (pointerToFile, "\n\n");
            continue;

            case 10:
                // Mode ini akan mencari dan menampilkan nilai rata-rata

                // User harus menginputkan parameter dari average (array) 
                // Keterangan parameter
                /*
                    * array, diketik saja pada terminal
                */
                // Ketika user menginputkan selain array
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do {
                    printf ("input: average("); scanf ("%[^)]s", tempStringInput); getchar ();
                    fprintf (pointerToFile, "input: average("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    strcpy (stringInput,token);
                } while (! (strcmp (stringInput,"array") == 0));

                puts ("Output:");
                printf ("Array:");
                fprintf (pointerToFile, "Output:\nArray:");
                printArray (array, longOfAssignedArray, pointerToFile);

                // Menggunakan sum yang memiliki nilai awal 0 untuk menyimpan penjumlahan
                // seluruh bilangan di dalam array menggunakan perulangan
                for (int i = 0; i < longOfAssignedArray; i++) {
                    sum += array[i];
                }

                // Tampilkan nilai rata-rata dengan cara nilai sum dibagi oleh nilai  longOfAssignedArray
                // Nilai yang ditampilkan adalah bilangan float yang memiliki bilangan 2 digit bilangan float
                // di belakang koma
                printf("Average: %d/%d = %.2f\n", sum, longOfAssignedArray, (float) sum/longOfAssignedArray);
                fprintf (pointerToFile, "Average: %d/%d = %.2f\n", sum, longOfAssignedArray, (float) sum/longOfAssignedArray);

                fprintf (pointerToFile, "\n\n");
            continue;

            case 11:
                // Mode ini akan mencari banyaknya bilangan ganjil
                // dan menampilkan bilangan-bilangam ganjil

                // User harus menginputkan parameter dari ganjil (array) 
                // Keterangan parameter
                /*
                    * array, diketik saja pada terminal
                */
                // Ketika user menginputkan selain array
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do {
                    printf ("input: ganjil("); scanf ("%[^)]s", tempStringInput); getchar ();
                    fprintf (pointerToFile, "input: ganjil("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    strcpy (stringInput,token);
                } while (! (strcmp (stringInput,"array") == 0));

                puts ("Output:");
                printf ("Array:");
                fprintf (pointerToFile, "Output:\nArray:");
                printArray (array, longOfAssignedArray, pointerToFile);

                printf ("Ganjil: ");
                fprintf (pointerToFile, "Ganjil: ");
                
                // Cek setiap elemen di dalam array. Apabila tidak habis dibagi dua,
                // maka bilangan tersebut adalah bilangan ganjil
                for (int i = 0; i < longOfAssignedArray; i++) {
                    if (array[i] % 2 != 0) {
                        
                        // Cara agar koma berada di belakang elemen ketika output
                        // Namun, mencegah koma untuk ditampilkan setelah 
                        // elemen paling terakhir
                        while (loopForRenoveComma < manyEvenOrOddNumber) {
                            printf(",");
                            fprintf (pointerToFile, ",");
                            loopForRenoveComma++;
                        }

                        // Melakukan increment setiap kondisi di atas terpenuhi
                        // terhdapat variabel  manyEvenOrOddNumber yang 
                        // akan digunakan untuk mengetahui seberapa banyak 
                        // nilai ganjil
                        manyEvenOrOddNumber++;
                        printf ("%d", array[i]);
                        fprintf (pointerToFile,"%d", array[i]);
                    }
                }
                printf("\n");
                fprintf (pointerToFile, "\n");
                printf("Jumlah bilangan ganjil: %d\n", manyEvenOrOddNumber);
                fprintf (pointerToFile, "Jumlah bilangan ganjil: %d\n", manyEvenOrOddNumber);

                fprintf (pointerToFile, "\n\n");
            continue;

            case 12:
                // Mode ini akan mencari banyaknya bilangan genap
                // dan menampilkan bilangan-bilangam genap

                // User harus menginputkan parameter dari genap (array) 
                // Keterangan parameter
                /*
                    * array, diketik saja pada terminal
                */
                // Ketika user menginputkan selain array
                // maka program akan meminta input ulang hingga user memasukkan input yang benar
                do {
                    printf ("input: genap("); scanf ("%[^)]s", tempStringInput); getchar ();
                    fprintf (pointerToFile, "input: genap("); fprintf (pointerToFile, "%s)\n", tempStringInput);
                    token = strtok (tempStringInput,",");
                    strcpy (stringInput,token);
                } while (! (strcmp (stringInput,"array") == 0));

                puts ("Output:");
                printf ("Array:");
                fprintf (pointerToFile, "Output:\nArray:");
                printArray (array, longOfAssignedArray, pointerToFile);

                printf ("Genap: ");
                fprintf (pointerToFile, "Genap: ");

                // Cek setiap elemen di dalam array. Apabila habis dibagi dua,
                // maka bilangan tersebut adalah bilangan genap
                for (int i = 0; i < longOfAssignedArray; i++) {
                    if (array[i] % 2 == 0) {
                        while (loopForRenoveComma < manyEvenOrOddNumber) {
                            printf(",");
                            fprintf (pointerToFile, ",");
                            loopForRenoveComma++;
                        }

                        // Melakukan increment setiap kondisi di atas terpenuhi
                        // terhdapat variabel  manyEvenOrOddNumber yang 
                        // akan digunakan untuk mengetahui seberapa banyak 
                        // nilai genap
                        manyEvenOrOddNumber++;
                        printf ("%d", array[i]);
                        fprintf (pointerToFile,"%d", array[i]);
                    }
                }
                printf("\n");
                printf("Jumlah bilangan genap: %d\n", manyEvenOrOddNumber);
                fprintf (pointerToFile, "Jumlah bilangan ganjil: %d\n", manyEvenOrOddNumber);

                fprintf (pointerToFile, "\n\n");
            continue;

            case 13:
            // Akan keluar dan menyimpan semua perintah file output
            // ke dalam file yang sudah ditentukan
            fclose (pointerToFile);
            return 0;

            case 14:
            // Keluar tanpa menyimpan
            return 0;

            default:
            puts("Pilih di antara angka 1-14");
            continue;
        }   
    }
}

void printArray (int* array, int longOfAssignedArray, FILE* pointerToFile) {
    for (int i = 0; i < longOfAssignedArray; i++)
        printf(" [%d]", array[i]);
    for (int i = 0; i < longOfAssignedArray; i++)
        fprintf(pointerToFile, " [%d]", array[i]);
    for (int i = 0; i < 20 - longOfAssignedArray; i++)
        printf(" []");
    for (int i = 0; i < 20 - longOfAssignedArray; i++)
        fprintf(pointerToFile, " []");
    fprintf(pointerToFile, "\n");
    puts("");
}

int isPrime (int random){
    int sqrtRandom = sqrt(random);
    if (random == 2 || random == 3){
        return 1;
    }
    else if (random == 0 || random == 1){
        return 0;
    }
    else{
        for (int randomNumDivider = 2; randomNumDivider <= sqrtRandom; randomNumDivider++){
            if (random % randomNumDivider == 0){
                return 0;   
            }
        }
        return 1;
    }
    return 0;
}

void swap (int* number1, int* number2) {
    int temp = 0;
    temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void init (int longOfAssignedArray, char NorP, int* array, int* unsortedArray){
    int a = 0, random, sqrtRandom;
    srand(time(0));
    if (NorP == 'n') {
        while(a < longOfAssignedArray){
            random = rand();
            srand(random);
            array[a] = random;
            unsortedArray[a] = random;
            a++;
        }
    }
    else if (NorP == 'p') {
        while(a < longOfAssignedArray) {
            random = rand();
            srand(random);
            if (isPrime(random)) {
                array[a] = random;
                unsortedArray[a] = random;
                a++;
            }
        }
    }
}

void sort (int* array, int longOfAssignedArray, char* pilUrut, int pilSorting) {
    int swapped, count = 0, tempAssignedArray = longOfAssignedArray;
    if (strcmp(pilUrut,"\"asc\"") == 0) {
        switch (pilSorting) {
        case 1:
            /* Bubble Sort */
            do {
                swapped = 0;
                for (int i = 0; i < tempAssignedArray - 1; i++) {
                    if (array[i] > array[i + 1]) {
                        swap(&array[i], &array[i + 1]);
                        swapped = 1;
                    }            
                }
                tempAssignedArray--;
            } while (swapped);
            break;

        case 2:
            /* Selection Sort*/
            while (count < longOfAssignedArray){
                int newMinimumIndex = count, count2 = count, minimum = array[count];
                while (count2 < longOfAssignedArray){
                    if (array[count2] < minimum){
                        newMinimumIndex = count2;
                        minimum = array[count2];
                    }
                    count2++;
                }
                swap(&array[newMinimumIndex], &array[count]);
                count++;
            }
            break;
            
        case 3:
            /* Insertion Sort*/
            do{
                int count2 = count;
                while (count2 > 0) {
                    if (array[count2] < array[count2 - 1]) {
                        swap(&array[count2], &array[count2 - 1]);
                    }
                    else {
                        break;
                    }
                    count2--;
                }
                count++;
            } while (count < longOfAssignedArray);
            break;
        }
    }
    else if (strcmp(pilUrut,"\"desc\"") == 0) {
        switch (pilSorting) {
            case 1:
                /* Bubble Sort */
                do {
                    swapped = 0;
                    for (int i = 0; i < tempAssignedArray - 1; i++) {
                        if (array[i] < array[i + 1]) {
                            swap(&array[i], &array[i + 1]);
                            swapped = 1;
                        }            
                    }
                    tempAssignedArray--;
                } while (swapped);
                break;

            case 2:
                /* Selection Sort*/
                while (count < longOfAssignedArray){
                    int newMinimumIndex = count, count2 = count, minimum = array[count];
                    while (count2 < longOfAssignedArray){
                        if (array[count2] > minimum){
                            newMinimumIndex = count2;
                            minimum = array[count2];
                        }
                        count2++;
                    }
                    swap(&array[newMinimumIndex], &array[count]);
                    count++;
                }
                break;
                
            case 3:
                /* Insertion Sort*/
                do{
                    int count2 = count;
                    while (count2 > 0)
                    {
                        if (array[count2] > array[count2 - 1]) {
                            swap(&array[count2], &array[count2 - 1]);
                        }
                        else{
                            break;
                        }
                        count2--;
                    }
                    count++;
                } while (count < longOfAssignedArray);
                break;
        }
    }
}

int search (int* array, int numberToFind, char* pilUrut, int longOfAssignedArray, int* findedNumberIndex) {
    int theFirst = 0, theLast = longOfAssignedArray, theMiddle = ((theFirst+theLast)/2);
    while (theFirst <= theLast){
        if (strcmp (pilUrut,"\"asc\"") == 0)
        {
            if(array[theMiddle] == numberToFind) {
                *findedNumberIndex = theMiddle;
                return 1;
            }
            else if (numberToFind < array[theMiddle]) {
                theLast = theMiddle - 1;
                theMiddle = ((theLast + theFirst) / 2);
            }
            else if (numberToFind > array[theMiddle]) {
                theFirst = theMiddle + 1;
                theMiddle = ((theLast + theFirst) / 2);
            }
            if (theFirst > theLast) {
                break;
            }
            
        }
        else if (strcmp (pilUrut,"\"desc\"") == 0) {
            if(array[theMiddle] == numberToFind) {
                *findedNumberIndex = theMiddle;
                return 1;
            }
            else if (numberToFind > array[theMiddle]) {
                theLast = theMiddle - 1;
                theMiddle = ((theLast + theFirst) / 2);
            }
            else if (numberToFind < array[theMiddle]) {
                theFirst = theMiddle + 1;
                theMiddle = ((theLast + theFirst) / 2);
            }
            if (theFirst > theLast) {
                break;
            }
        }
    } 
    return 0;
}

int insert (int* array, int numbertoInsert, char* pilUrut, int* longOfAssignedArray) {
    int leftOfSortedArray[20], rightOfSortedArray[20], indexOfLeftElement, indexOfRightElement;
    if (*longOfAssignedArray <= 19) {
        if (strcmp(pilUrut,"\"asc\"") == 0){
            for (int i = 0; i < *longOfAssignedArray; i++) {
                if (i == 0 && numbertoInsert < array[i]) {
                    indexOfLeftElement = -1;
                    indexOfRightElement = i;
                    for (int j = indexOfRightElement; j < *longOfAssignedArray; j++) {
                        rightOfSortedArray[j] = array[j];
                    }
                    break;
                }
                else if (array[i-1] < numbertoInsert && array[i] > numbertoInsert) {
                    indexOfLeftElement = i - 1;
                    indexOfRightElement = i;
                    for (int j = 0; j <= indexOfLeftElement; j++) {
                        leftOfSortedArray[j] = array[j];
                    }
                    for (int j = indexOfRightElement; j < *longOfAssignedArray; j++) {
                        rightOfSortedArray[j] = array[j];
                    }
                    break;
                }
                else if (i == *longOfAssignedArray - 1 && numbertoInsert > array[i]) {
                    indexOfRightElement = *longOfAssignedArray;
                    indexOfLeftElement = *longOfAssignedArray - 1;
                    for (int j = 0; j <= indexOfLeftElement; j++) {
                        leftOfSortedArray[j] = array[j];
                    }
                }
            }
        }
        else if(strcmp(pilUrut,"\"desc\"") == 0)
        {
             for (int i = 0; i < *longOfAssignedArray; i++) {
                if (i == 0 && numbertoInsert > array[i]) {
                    indexOfLeftElement = -1;
                    indexOfRightElement = i;
                    for (int j = indexOfRightElement; j < *longOfAssignedArray; j++) {
                        rightOfSortedArray[j] = array[j];
                    }
                    break;
                }
                else if (array[i-1] < numbertoInsert && array[i] > numbertoInsert) {
                    indexOfLeftElement = i - 1;
                    indexOfRightElement = i;
                    for (int j = 0; j <= indexOfLeftElement; j++) {
                        leftOfSortedArray[j] = array[j];
                    }
                    for (int j = indexOfRightElement; j < *longOfAssignedArray; j++) {
                        rightOfSortedArray[j] = array[j];
                    }
                    break;
                }
                else if (i == *longOfAssignedArray - 1 && numbertoInsert < array[i]) {
                    indexOfRightElement = *longOfAssignedArray;
                    indexOfLeftElement = *longOfAssignedArray - 1;
                    for (int j = 0; j <= indexOfLeftElement; j++) {
                        leftOfSortedArray[j] = array[j];
                    }
                }
            }
        }

        for (int i = 0; i <= indexOfLeftElement; i++) {
            array[i] = leftOfSortedArray[i];
        }
        *longOfAssignedArray = *longOfAssignedArray + 1;
        array[indexOfLeftElement + 1] = numbertoInsert;
        for (int i = indexOfRightElement + 1; i < *longOfAssignedArray; i++) {
            array[i] = rightOfSortedArray[i - 1];
        }
        return 1;
    }
    else {
        return 0;
    }
    
}