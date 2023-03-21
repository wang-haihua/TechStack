package main.java.com.beverageStore.observer;

import java.util.ArrayList;
import java.util.List;

public class ImplCustomer implements Customer {

	private List<Observer> observers = new ArrayList<Observer>();
	private String msg;
	
	@Override
	public void registerObserver(Observer observer) {
		// TODO Auto-generated method stub
		observers.add(observer);
	}

	@Override
	public void removeObserver(Observer observer) {
		// TODO Auto-generated method stub
		int index = observers.indexOf(observer);
		if (index >= 0)
		{
			observers.remove(index);
		}

	}

	@Override
	public void notifyObservers() {
		// TODO Auto-generated method stub
		for (Observer observer : observers)
		{
			observer.update(msg);
		}

	}

	/**
	 * 主题更新消息
	 * 
	 * @param msg
	 */
	public void setMsg(String msg)
	{
		this.msg = msg;
		
		notifyObservers();
	}

}
