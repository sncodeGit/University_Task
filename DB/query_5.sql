SELECT film_id, title 
FROM film
WHERE film_id
NOT IN
(SELECT DISTINCT film_id
FROM inventory, rental 
WHERE
inventory.inventory_id = rental.inventory_id);
