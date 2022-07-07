{

   int shmid;
   int pid;
   sem_t * full;
   sem_t * empty;
   sem_t * mutex;
   void * buf;


  if((shmid =  shmget(KEY, SIZE, IPC_CREAT| 0666)) == -1)
  {
       perror("could not create shared memory");
       exit(1);
  }


  if( (buf = shmat(shmid, 0, 0)) == (void*)-1)
  {
      perror("could not attach the memory ");
      exit(1);
  }

 full = (sem_t*) buf;
  buf  = buf + sizeof(sem_t);
  empty = (sem_t*) buf;
  buf = buf + sizeof(sem_t);
  mutex = (sem_t*) buf;
  buf = buf + sizeof(sem_t);



  if(sem_init(full, 1, 0) <0)
  {
       perror("could not init the semaphore full");
       exit(1);
  }

  if(sem_init(empty, 1, N ) <0)
  {
       perror("could not init the semaphore empty");
       exit(1);
  }

  if(sem_init(mutex, 1, 1 ) <0)
  {
           perror("could not init the semaphore empty");
       exit(1);
  }

  pid = fork();

  if(pid == 0)  // producer process
  {




     while(1)
     {
         sleep(1);
         if(sem_wait(empty) <0)
         {
           perror("cannot decrement semaphore");
           exit(1);
         }

        if(sem_wait(mutex) <0)
         {
           perror("cannot decrement semaphore");
           exit(1);
         }

           printf("PRODUCER produces an item\n" );

         if(sem_post(mutex) < 0)
         {
             perror("cannot increment the semaphore");
             exit(1);
         }

        if(sem_post(full) < 0)
         {
            perror("cannot increment the semaphore");
            exit(1);
         }

      }
}
else  // consumer process
{

  time_t t;


   while(1)
   {
      srand((unsigned) time(&t));
     sleep(rand()%5);


      if(sem_wait(full) <0)
       {
           perror("cannot decrement semaphore");
                   exit(1);
       }

        if(sem_wait(mutex) <0)
         {
           perror("cannot decrement semaphore");
           exit(1);
         }

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  13,1          36%
