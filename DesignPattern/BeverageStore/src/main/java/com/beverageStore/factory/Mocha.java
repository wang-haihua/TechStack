package main.java.com.beverageStore.factory;

public class Mocha extends Beverage {

	public Mocha() {
		// TODO Auto-generated constructor stub
		this.name = "Mocha";
		this.description = "Mocha";
		this.price = 22.0;
	}
	
	@Override
	public Double cost() {
		// TODO Auto-generated method stub
		return this.getPrice();
	}

}
