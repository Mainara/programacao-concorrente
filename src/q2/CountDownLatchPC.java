package q2;


public class CountDownLatchPC
{ 
	private int threadNum;
	
	
	public CountDownLatchPC(int threadNum) {
		this.threadNum = threadNum;
	}
	
	public synchronized void await() {
		try {
			wait();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	
	public synchronized void countDown() {
		--this.threadNum;
		
		if (this.threadNum <= 0) {
			notifyAll();
		}
	}
	
	
    public static void main(String args[])  
                   throws InterruptedException 
    { 
        // Let us create task that is going to  
        // wait for four threads before it starts 
        CountDownLatchPC latch = new CountDownLatchPC(4); 
  
        // Let us create four worker  
        // threads and start them. 
        Worker first = new Worker(1000, latch,  
                                  "WORKER-1"); 
        Worker second = new Worker(2000, latch,  
                                  "WORKER-2"); 
        Worker third = new Worker(3000, latch,  
                                  "WORKER-3"); 
        Worker fourth = new Worker(4000, latch,  
                                  "WORKER-4"); 
        first.start(); 
        second.start(); 
        third.start(); 
        fourth.start(); 
  
        // The main task waits for four threads 
        latch.await(); 
  
        // Main thread has started 
        System.out.println(Thread.currentThread().getName() + 
                           " has finished"); 
    } 
} 
  
// A class to represent threads for which 
// the main thread waits. 
class Worker extends Thread 
{ 
    private int delay; 
    private CountDownLatchPC latch; 
  
    public Worker(int delay, CountDownLatchPC latch, 
                                    String name) 
    { 
        super(name); 
        this.delay = delay; 
        this.latch = latch; 
    } 
  
    @Override
    public void run() 
    { 
        try
        { 
            Thread.sleep(delay); 
            latch.countDown();
            System.out.println(Thread.currentThread().getName() 
                            + " finished"); 
        } 
        catch (InterruptedException e) 
        { 
            e.printStackTrace(); 
        } 
    } 
} 