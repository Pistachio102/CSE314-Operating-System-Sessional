package nachos.ag;


import nachos.threads.*;
import nachos.machine.*;


public class ThreadTest{
    public static void initiateTest(){
        JoinTest.performTest();
        System.out.println("Starting Alarm Test");
        Alarm alarm = new Alarm();
        KThread t1 = new KThread(new AlarmTest(alarm,10000)).setName("T1");
        KThread t2 = new KThread(new AlarmTest(alarm,20000)).setName("T2");

        alarm.waitUntil(10000);
        t1.fork();
        alarm.waitUntil(20000);
        t2.fork();
//        alarm.waitUntil(350000);

        t1.join();
        t2.join();
        System.out.println("Alarm Test finished");
        KThread.yield();
//
        ComTest comTest = new ComTest();
        comTest.performTest();
//        ComTest.conditionTest1();

    }
}

class JoinTest{
    public static void performTest(){
        System.out.println("Starting Join Task");
        KThread t0 = new KThread(new Runnable() {
            @Override
            public void run() {
                for (int i = 0; i < 5 ; i++) {
                    System.out.println("t0 looped "+i);
                }
            }
        }).setName("t0");
        t0.fork();
        t0.join();

        KThread t1 = new KThread(new Runnable() {
            @Override
            public void run() {
                for (int i = 0; i < 5 ; i++) {
                    System.out.println("t1 looped "+i);
                }
            }
        }).setName("t1");

        t1.fork();
        t1.join();

        KThread t2 = new KThread(new Runnable() {
            @Override
            public void run() {
                for (int i = 0; i < 5 ; i++) {
                    System.out.println("t2 looped "+i);
                }
            }
        }).setName("t2");
        t2.fork();
        t2.join();

        System.out.println("Join task finished");
    }
}

class AlarmTest implements Runnable{
    AlarmTest(Alarm alarm,long argTime){
        this.alarm = alarm;
        time = argTime;

    }
    Alarm alarm;
    long time;
    @Override
    public void run() {
        System.out.println(KThread.currentThread().getName()+" rings at "+ Machine.timer().getTime());
        alarm.waitUntil(time);
        System.out.println(KThread.currentThread().getName()+" rings at "+ Machine.timer().getTime());
    }
}

class ComTest{
    private Communicator com;
    ComTest(){
        com= new Communicator();
    }

    public void performTest(){
        System.out.println("testing for task 2 & 4 initiated");
        System.out.println("--------------------------------");

//        Communicator comm = new Communicator();
//        new KThread(new Speaker(comm)).fork();
//        new KThread(new Listener(comm)).fork();
//        new KThread(new Listener(comm)).fork();
//        new KThread(new Speaker(comm)).fork();
//        new KThread(new Listener(comm)).fork();
//        new KThread(new Listener(comm)).fork();
//        new KThread(new Speaker(comm)).fork();
//        KThread s1= new KThread(new Speaker(comm)).fork();

//        KThread l1 = new KThread(new Listener(com)).setName("L1");
//        KThread l2 = new KThread(new Listener(com)).setName("L2");
//        KThread l3 = new KThread(new Listener(com)).setName("L3");
//
//        KThread s1 = new KThread(new Speaker(com)).setName("S1");
//        KThread s2 = new KThread(new Speaker(com)).setName("S2");
//        KThread s3 = new KThread(new Speaker(com)).setName("S3");
//
//        l1.fork();
//        l2.fork();
//        s1.fork();
//        s2.fork();
//        s3.fork();
//        l3.fork();
//      KThread.yield();
//        s1.join();
//        s2.join();
//        s3.join();

//        l3.join();
//        l1.join();
//        l2.join();

        communicatorTest3();

        System.out.println("------------------------------");
        System.out.println("testing for task2 & 4 finished");
    }

//    private static  class Listener implements Runnable{
//        private int which;
//        private  Communicator com;
//        Listener(int which,Communicator com){
//            this.which = which;
//            this.com= com;
//        }
//
//        @Override
//        public void run() {
//            for (int i = 0; i < 3; i++) {
//                KThread.yield();
//                com.listen();
//                KThread.yield();
//            }
//        }
//    }

    private static class Listener implements Runnable {
        static int id = 0;
        private int localID;
        Listener(Communicator comm)
        {
            communicator = comm;
            localID = id++;
        }
        public void run() {
            System.out.println("L" + localID + ":I'm listening for a word");
            System.out.println("L" + localID + ":I got the word -> " + communicator.listen());
            KThread.yield();

        }
        private Communicator communicator;
    }
    private static class Speaker implements Runnable {
        static int id = 0;
        private int localID;
        Speaker(Communicator comm)
        {
            localID= id++;
            communicator = comm;
            //System.out.println("spekaer");
        }
        public void run() {
            System.out.println("S" + localID + ":I'm Speaking my ID number -> " + localID);
            communicator.speak(localID);
            KThread.yield();

        }
        private Communicator communicator;
    }
    public static void communicatorTest1()
    {
        /*
         * Tests 1 listener and 1 speaker, listener spawns first
         */
        Communicator comm = new Communicator();
        KThread l1 = new KThread(new Listener(comm));
        KThread s1 = new KThread(new Speaker(comm));

        s1.fork();
        l1.fork();

        l1.join();
        s1.join();

    }
    public static void communicatorTest2()
    {
        /*
         * Tests 1 listener and 1 speaker, speaker spawns first
         */
        Communicator comm = new Communicator();
        KThread s1 = new KThread(new Speaker(comm)).setName("s1");
        KThread l1 = new KThread(new Listener(comm)).setName("l1");
        s1.fork();
        l1.fork();
        s1.join();
        l1.join();
    }

    public static void communicatorTest3()
    {
        /*
         * Tests many listeners and one speaker
         */
        System.out.println("com test test started ");
        Communicator comm = new Communicator();
        KThread s1=new KThread(new Speaker(comm));
        KThread s2=new KThread(new Speaker(comm));
        KThread s3=new KThread(new Speaker(comm));

        KThread l1=new KThread(new Listener(comm));
        KThread l2=new KThread(new Listener(comm));
        KThread l3=new KThread(new Listener(comm));


        s1.fork();
        s2.fork();
        s3.fork();
        l1.fork();
        l2.fork();
        l3.fork();


        s1.join();
        s2.join();
        s3.join();
        l1.join();
        l2.join();
        l3.join();

    }


//    private static  class Speaker implements Runnable{
//        private int which;
//        private  Communicator com;
//        Speaker(int which,Communicator com){
//            this.which = which;
//            this.com= com;
//        }
//
//        @Override
//        public void run() {
//            for (int i = 0; i < 2; i++) {
//                KThread.yield();
//                com.speak(i);
//                KThread.yield();
//            }
//        }
//    }
public static void conditionTest1()
{
    /*
     * Tests condition2 by spawning a thread that goes to sleep and
     * is waken up by the main thread
     */
    System.out.println("Condition TEST #1: Start");
    final Lock lock = new Lock();
    final Condition2 condition = new Condition2(lock);
    KThread thread1 = new KThread(new Runnable(){
        public void run(){
            lock.acquire();
            System.out.println("Thread is going to sleep");
            condition.sleep();
            System.out.println("Thread has been woken up");
            lock.release();
        }
    }).setName("thread1");
    KThread thread2 = new KThread(new Runnable(){
        public void run(){
            lock.acquire();
            System.out.println("Thread is going to sleep");
            condition.sleep();
            System.out.println("Thread has been woken up");
            lock.release();
        }
    }).setName("thread2");
    KThread thread3 = new KThread(new Runnable(){
        public void run(){
            lock.acquire();
            System.out.println("Thread is going to sleep");
            condition.sleep();
            System.out.println("Thread has been woken up");
            lock.release();
        }
    }).setName("thread3");
    thread1.fork();
    thread2.fork();
    thread3.fork();
    thread1.join();
    thread2.join();
    thread3.join();
    System.out.println("Main: yielding to run the other thread");
    KThread.yield();
    System.out.println("Main: sending the wake signal then yeilding");
    lock.acquire();
    condition.wakeAll();
    lock.release();

    KThread.yield();


    System.out.println("Condition TEST #1: End");
}
}
