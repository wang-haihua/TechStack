package main.java.com.beverageStore.strategy;

import java.math.BigDecimal;

public class PlatinumMemberDiscount implements Discount {

	@Override
	public BigDecimal priceAfterDiscount(BigDecimal orderPrice) {
		// TODO Auto-generated method stub
		int payPrice = orderPrice.intValue();
		return new BigDecimal(payPrice * 0.6);
	}

}
