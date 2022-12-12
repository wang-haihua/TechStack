package main.java.com.beverageStore.factory;

public abstract class Beverage {

	protected String name;
	protected Double price;
	protected String description;
    
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public double getPrice() {
		return price;
	}
	public void setPrice(Double price) {
		this.price = price;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
    
	public abstract Double cost();
	
}
