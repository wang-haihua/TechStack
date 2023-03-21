package main.java.com.beverageStore.decorater;

import main.java.com.beverageStore.factory.Beverage;

public abstract class Weight extends Beverage {

	Beverage beverage;
	
	Weight(Beverage decoratedBeverage){
		this.beverage = decoratedBeverage;
	}
	
	public String getDescription() {
		return beverage.getDescription() + " " + super.getDescription();
	}
	
	
	public Double cost() {
		// TODO Auto-generated method stub
		return super.getPrice()+beverage.cost();
	}
}
