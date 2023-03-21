package main.java.com.beverageStore.factory;

public class MatchaMilkTea extends Beverage {

	public MatchaMilkTea() {
		// TODO Auto-generated constructor stub
		this.name = "Matcha Milk Tea";
		this.description = "Matcha Milk Tea";
		this.price = 14.0;
	}
	
	@Override
	public Double cost() {
		// TODO Auto-generated method stub
		return this.getPrice();
	}

}
