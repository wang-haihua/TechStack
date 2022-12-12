package main.java.com.beverageStore.factory;

public class Cappuccino extends Beverage {

	public Cappuccino() {
		// TODO Auto-generated constructor stub
		this.name = "Cappuccino";
		this.description = "Cappuccino";
		this.price = 24.0;
	}
	
	@Override
	public Double cost() {
		// TODO Auto-generated method stub
		return this.getPrice();
	}

}
