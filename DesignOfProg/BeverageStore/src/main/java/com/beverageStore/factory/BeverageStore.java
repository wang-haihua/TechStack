package main.java.com.beverageStore.factory;

public abstract class BeverageStore {

	abstract Beverage createBeverage(String item);
	
	public Beverage orderBeverage(String type) {
		Beverage beverage = createBeverage(type);
		System.out.println("--- Making a " + beverage.getName() +" ---");
		
		return beverage;
	}
}
