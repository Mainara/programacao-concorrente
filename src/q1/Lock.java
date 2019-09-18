package q1;

import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.LockSupport;


class Count {
	private int count;
	
	public int get() {
		return this.count;
	}
	
	public void inc(int v) {
		this.count += v;
	}
}


class TCount implements Runnable {
	
	private Count count;
	private Lock l;
	
	public TCount(Count count, Lock l) {
		this.count = count;
		this.l = l;
	}
	
	public void run() {
		for(int i = 0; i < 1000; i++) {
			l.lock();
			this.count.inc(1);
			System.out.println(Thread.currentThread().getId() + ": " + this.count.get());
			l.unlock();
		}
	}
}


public class Lock {
	private volatile AtomicBoolean flag;
	private volatile AtomicBoolean guard;
	private volatile ArrayList<Thread> queue;
	
	public Lock() {
		this.flag = new AtomicBoolean(false);
		this.guard = new AtomicBoolean(false);
		this.queue = new ArrayList<>();
	}

	public void lock() {
		while(this.guard.getAndSet(true)) {
		}
		
		if (this.flag.getAndSet(true)) {
			this.queue.add(Thread.currentThread());
			this.guard.getAndSet(false);
			LockSupport.park();
		} else {
			this.guard.getAndSet(false);
		}
	}
	
	public void unlock() {
		while(this.guard.getAndSet(true)) {
		}
		
		if (!this.queue.isEmpty()) {
			Thread thread = this.queue.get(0);
			this.queue.remove(0);
			this.guard.getAndSet(false);
			LockSupport.unpark(thread);
		} else {
			this.flag.getAndSet(false);
			this.guard.getAndSet(false);
		}
	}
	
	public static void main(String[] args) {
		System.out.println("Print");
		Count c = new Count();
		Lock l = new Lock();
		
		Thread t1 = new Thread(new TCount(c, l));
		Thread t2 = new Thread(new TCount(c, l));
		Thread t3 = new Thread(new TCount(c, l));
		Thread t4 = new Thread(new TCount(c, l));
		Thread t5 = new Thread(new TCount(c, l));
		Thread t6 = new Thread(new TCount(c, l));
		
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		t5.start();
		t6.start();
		
	}
}
