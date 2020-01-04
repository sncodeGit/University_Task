SELECT first_name, last_name, SUM(amount) AS rent_amount_sum
FROM customer, payment
WHERE customer.customer_id = payment.customer_id
GROUP BY customer.customer_id;
