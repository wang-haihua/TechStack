package main.java.com.beverageStore.observer;

public class CounterObserver implements Observer {

	private Customer customer;
	
	public CounterObserver(Customer customer) {
		this.customer = customer;
		customer.registerObserver(this);
	}
	
	@Override
	public void update(String msg) {
		// TODO Auto-generated method stub
		System.out.println("The customer's order includes " + msg);
		
	}

}
