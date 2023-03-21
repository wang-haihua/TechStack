package main.java.com.beverageStore.strategy;

import java.math.BigDecimal;

public interface Discount {

	public BigDecimal priceAfterDiscount(BigDecimal orderPrice);
}
