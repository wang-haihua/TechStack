package main.java.com.beverageStore.observer;

public class CustomerTestDrive {
	public static void main(String[] args)
	{
		ImplCustomer implCustomer = new ImplCustomer();
		
		Observer observer2 = new BackKitchenObserver(implCustomer);
		Observer observer1 = new CounterObserver(implCustomer);
 
		implCustomer.setMsg("HongKongMilkTea");
		implCustomer.setMsg("Mocha");
		
	}

}
