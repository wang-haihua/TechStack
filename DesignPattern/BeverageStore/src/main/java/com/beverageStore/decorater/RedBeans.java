package main.java.com.beverageStore.decorater;

import main.java.com.beverageStore.factory.Beverage;

public class RedBeans extends Material {

	public RedBeans(Beverage beverage) {
		// TODO Auto-generated constructor stub
		super(beverage);
		this.setPrice(1.0);
		this.setDescription("RedBeans");
	}
}
