package q4;


import java.util.HashMap;
import java.util.Map;

import org.mapdb.DB;
import org.mapdb.DBMaker;
import org.mapdb.HTreeMap;

public class CacheMap<k, v> {
	
	private HTreeMap<k, v> map;
	private int cacheSize;
	private HashMap<k, v> cache;
	private int timeoutSecs;
	
	public CacheMap(int cacheSize, int timeoutSecs, HTreeMap<k, v> map) {
		this.map = map;
		this.cacheSize = cacheSize;
		this.cache = new HashMap<k, v>();
		this.timeoutSecs = timeoutSecs;
		
		clearCacheAfterTimeout();
	}
	
	private void clearCacheAfterTimeout() {
		Thread t = new Thread(new Runnable() {
			
			@Override
			public void run() {
				
				while (true) {
					try {
						Thread.sleep(timeoutSecs*1000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					
					moveCacheToMap();
				}
			}
		});
		
		t.start();
	}
	
	private void moveCacheToMap() {
		synchronized (this) {
			cache.forEach((k, v) -> {
				map.put(k, v);
			});
			
			cache.clear();
		}
	}
	
	public void clear() {
		synchronized (this) {
			cache.clear();
			map.clear();
		}
	}
	
	public boolean containsKey(Object key) {
		return cache.containsKey(key) || map.containsKey(key);
	}
	
	public v get(k key) {
		v value = cache.get(key);
		
		if (value == null) {
			value = map.get(key);
		}
		
		return value;
	}
	
	public boolean isEmpty() {
		synchronized (this) {
			return cache.isEmpty() && map.isEmpty();
		}
	}
	
	public void put(k key, v value) {
		synchronized (this) {
			if (cache.size() == cacheSize)
				moveCacheToMap();
			
			cache.put(key, value);
		}
	}
	
	public void remove(k key, v object) {
		synchronized (this) {
			cache.remove(key);
			map.remove(key);
		}
	}
	
	public int size() {
		int size = map.size();
		map.entrySet();

		for (Map.Entry<k, v> entry : cache.entrySet()) {
			size += (map.containsKey(entry.getKey())) ? 0 : 1;
		}
		
		return size;
	}
	
	public static void main(String[] args) {
		System.out.println("Hello!!!!!!!!!!");
		DB db = DBMaker.fileDB("teste.db").make();
		@SuppressWarnings("unchecked")
		HTreeMap<Integer, String> map = (HTreeMap<Integer, String>) db.hashMap("map").createOrOpen();
		CacheMap<Integer, String> cacheMap = new CacheMap<Integer, String>(5, 5, map);
		cacheMap.put(2, "Teste");
		cacheMap.put(4, "Outro");
		cacheMap.put(5, "TST");
		cacheMap.put(6, "Ola");
		cacheMap.put(7, "7");
		cacheMap.put(8, "8");
		cacheMap.put(9, "9");
		cacheMap.put(10, "10");
		
		System.out.println(cacheMap.size());
		System.out.println(map.size());
		
		try {
			Thread.sleep(10*1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		System.out.println(cacheMap.get(2));
		System.out.println(cacheMap.get(4));
		System.out.println(cacheMap.get(5));
		System.out.println(cacheMap.get(6));
		System.out.println(cacheMap.get(7));
		System.out.println(cacheMap.get(8));
		map.close();
	}

}
