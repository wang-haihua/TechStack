package main.java.com.beverageStore.factory;

public class WheatFragrantMilkTea extends Beverage {

	public WheatFragrantMilkTea() {
		// TODO Auto-generated constructor stub
		this.name = "Wheat Fragrant Milk Tea";
		this.description = "Wheat Fragrant Milk Tea";
		this.price = 16.0;
	}
	
	@Override
	public Double cost() {
		// TODO Auto-generated method stub
		return this.getPrice();
	}

}
