#include<iostream>
#include<cstdio>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<cstring>
#include <time.h>
#include <random>
#include <ctime>
using namespace std;

#define number_of_servicemen 5 // Number of semaphores for servicemen
#define number_of_cyclists 10 // Number of threads for cyclists
#define arr_size 1 // To initialize the servicemen semaphores
#define room_size 3 // To initialize the empty_room sem

int payment_room_occupied_by = 0, servicemen_in_use = 0, want_to_depart = 0;
sem_t servicemen[number_of_servicemen];
sem_t empty_room, departure_line;
pthread_mutex_t mutex, mutex2;

void* pay_bill(void* arg);
void* depart(void* arg);


void* service(void* arg){

   // int number_of_services = 0;
   while(true)
   {
       if(want_to_depart == 0)
        break;
       else continue;
   }

    for(int i = 0; i < number_of_servicemen; i++)
    {
        sem_wait(&servicemen[i]);
        pthread_mutex_lock(&mutex);
        cout << (char*)arg << " started taking service from serviceman " << i << endl;
        servicemen_in_use++;
        pthread_mutex_unlock(&mutex);
        sleep(1 + rand() % 3);
        pthread_mutex_lock(&mutex);
        cout << (char*)arg << " finished taking service from serviceman " << i << endl;
        servicemen_in_use--;
        pthread_mutex_unlock(&mutex);
        sem_post(&servicemen[i]);




        }
        pay_bill(arg);



    }





void* pay_bill(void* arg)
{
        sem_wait(&empty_room);
        pthread_mutex_lock(&mutex);
        payment_room_occupied_by++;
        cout << (char*)arg << " started paying the service bill." << endl;
        pthread_mutex_unlock(&mutex);
        sleep(1 + rand() % 4);
        pthread_mutex_lock(&mutex);
        cout << (char*)arg << " finished paying the service bill." << endl;
        payment_room_occupied_by--;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty_room);
        depart(arg);

}


void* depart(void* arg)
{
        sem_wait(&departure_line);
        pthread_mutex_lock(&mutex);
        want_to_depart++;
        pthread_mutex_unlock(&mutex);

        while(true)
        {
          if(servicemen_in_use == 0)
          break;
          else continue;
        }
        pthread_mutex_lock(&mutex);
        cout << (char*)arg << " has departed." << endl;
        want_to_depart--;
        pthread_mutex_unlock(&mutex);
        sem_post(&departure_line);


}




int main(int argc, char* argv[])
{
    int res;

// Initializing servicemen as semaphores.....

    for(int i = 0; i < number_of_servicemen; i++)
    {
        res = sem_init(&servicemen[i],0,arr_size);
        if(res != 0)
        {
        cout << "Failed to initialize semaphore number : " << i << endl;
        }
    }


// Initializing empty_room semaphore.....

    res = sem_init(&empty_room,0,room_size);
        if(res != 0)
        {
        cout << "Failed to initialize empty_room semaphore." << endl;
        }

        res = sem_init(&departure_line,0,arr_size);
        if(res != 0)
        {
        cout << "Failed to initialize departure_line semaphore." << endl;
        }

// Initializing mutex.....
    res = pthread_mutex_init(&mutex,NULL);
     if(res != 0)
     {
         cout << "Failed to initialize mutex." << endl;
     }


// Initializing mutex2.....
    res = pthread_mutex_init(&mutex2,NULL);
     if(res != 0)
     {
         cout << "Failed to initialize mutex2." << endl;
     }

// Initializing cyclists as threads.....

    pthread_t cyclists[number_of_cyclists];
    for(int i = 0; i < number_of_cyclists; i++)
    {
        char *id = new char[3];
        strcpy(id,to_string(i).c_str());

        res = pthread_create(&cyclists[i],NULL,service,(void *)id);

        if(res != 0)
        {
            cout << "Failed to create thread number : " << i << endl;
        }
    }

// Joining all the cyclist threads.....

    for(int i = 0; i < number_of_cyclists; i++){
        void *result;
        pthread_join(cyclists[i],&result);
       // printf("%s",(char*)result);
    }

// Destroying servicemen semaphores.....

    for(int i = 0; i < number_of_servicemen; i++)
    {
        res = sem_destroy(&servicemen[i]);
        if(res != 0)
        {
        cout << "Failed to destroy semaphore number : " << i << endl;
        }
    }


// Destroying empty_room semaphore.....

    res = sem_destroy(&empty_room);
        if(res != 0)
        {
        cout << "Failed to destroy empty_room semaphore." << endl;
        }


        res = sem_destroy(&departure_line);
        if(res != 0)
        {
        cout << "Failed to destroy departure_line semaphore." << endl;
        }

// Destroying mutex.....

     res = pthread_mutex_destroy(&mutex);
     if(res != 0)
     {
      cout << "Failed to destroy mutex." << endl;
     }

// Destroying mutex2.....

     res = pthread_mutex_destroy(&mutex2);
     if(res != 0)
     {
      cout << "Failed to destroy mutex2." << endl;
     }


    return 0;
}
