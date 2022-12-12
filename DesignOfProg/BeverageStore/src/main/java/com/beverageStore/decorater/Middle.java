package main.java.com.beverageStore.decorater;

import java.math.BigDecimal;

import main.java.com.beverageStore.factory.Beverage;

public class Middle extends Weight {

	public Middle(Beverage beverage) {
		// TODO Auto-generated constructor stub
		super(beverage);
		this.setPrice(0.0);
		this.setDescription("Middle");
	}

}
