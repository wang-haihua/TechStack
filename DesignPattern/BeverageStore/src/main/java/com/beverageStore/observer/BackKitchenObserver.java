package main.java.com.beverageStore.observer;

public class BackKitchenObserver implements Observer {

	private Customer customer;
	
	public BackKitchenObserver(Customer customer) {
		this.customer = customer;
		customer.registerObserver(this);
	}
	
	@Override
	public void update(String msg) {
		// TODO Auto-generated method stub
		System.out.println("The customer has ordered the " + msg);
	}

}
