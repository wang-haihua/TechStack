package main.java.com.beverageStore.factory;

public class VanillaLatte extends Beverage {

	public VanillaLatte() {
		// TODO Auto-generated constructor stub
		this.name = "VanillaLatte";
		this.description = "VanillaLatte";
		this.price = 26.0;
	}
	
	@Override
	public Double cost() {
		// TODO Auto-generated method stub
		return this.getPrice();
	}

}
