package q4;


import java.util.HashMap;

import org.mapdb.DB;
import org.mapdb.DBMaker;
import org.mapdb.HTreeMap;

public class CacheMap {
	
	private HTreeMap<Object, Object> map;
	private int cacheSize;
	private HashMap<Object, Object> cache;
	private int timeoutSecs;
	
	public CacheMap(int cacheSize, int timeoutSecs, HTreeMap<Object, Object> map) {
		this.map = map;
		this.cacheSize = cacheSize;
		this.cache = new HashMap<Object, Object>();
		this.timeoutSecs = timeoutSecs;
	}
	
	public void clear() {
		// TODO Auto-generated method stub

	}
	
	public void containsKey() {
		// TODO Auto-generated method stub

	}
	
	public void get() {
		// TODO Auto-generated method stub

	}
	
	public void isEmpty() {
		// TODO Auto-generated method stub

	}
	
	public void put(Object key, Object object) {
		// TODO Auto-generated method stub

	}
	
	public void remove(Object key, Object object) {
		// TODO Auto-generated method stub

	}
	
	public void size() {
		// TODO Auto-generated method stub

	}
	
	public static void main(String[] args) {
		System.out.println("Hello!!!!!!!!!!");
		DB db = DBMaker.fileDB("teste.db").make();
		@SuppressWarnings("unchecked")
		HTreeMap<Integer, String> map = (HTreeMap<Integer, String>) db.hashMap("map").createOrOpen();
		System.out.println(map.get(2));
		map.close();
	}

}
