package main.java.com.beverageStore.observer;

public interface Customer {
	/**
	 * 注册一个观察着
	 * 
	 * @param user
	 */
	public void registerObserver(Observer observer);
 
	/**
	 * 移除一个观察者
	 * 
	 * @param observer
	 */
	public void removeObserver(Observer observer);
 
	/**
	 * 通知所有的观察着
	 */
	public void notifyObservers();
}
