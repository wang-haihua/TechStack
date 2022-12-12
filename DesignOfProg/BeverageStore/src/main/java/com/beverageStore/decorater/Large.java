package main.java.com.beverageStore.decorater;

import java.math.BigDecimal;

import main.java.com.beverageStore.factory.Beverage;

public class Large extends Weight {

	public Large(Beverage beverage) {
		// TODO Auto-generated constructor stub
		super(beverage);
		this.setPrice(2.0);
		this.setDescription("Large");
	}

}
