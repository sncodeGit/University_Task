SELECT country, COUNT(customer_id) AS clients_count
FROM customer, address, city, country
WHERE customer.address_id = address.address_id
AND address.city_id = city.city_id
AND city.country_id = country.country_id
GROUP BY country.country_id;
