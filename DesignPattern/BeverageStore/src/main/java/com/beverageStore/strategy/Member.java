package main.java.com.beverageStore.strategy;

import java.math.BigDecimal;

public abstract class Member {

	Gift gift;
	Discount discount;
	private String rank;
	
	public Member(){};
	
	public void setGift(Gift gf) {
		gift = gf;
	}
	
	public void setDiscount(Discount dis) {
		discount = dis;
	}
	
	public void setRank(String rk) {
		rank = rk;
	}
	
	public void ifHasGift() {
		gift.giveaway();
	}
	
	public double whichDiscount(BigDecimal orderPrice) {
		return discount.priceAfterDiscount(orderPrice).doubleValue();
	}

	public String getRank() {
		return rank;
	}
}
