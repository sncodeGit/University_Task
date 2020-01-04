WITH rental_count_by_film AS 
(
SELECT film_id, 
COUNT(inventory.inventory_id) 
AS count_film 
FROM inventory, rental
WHERE inventory.inventory_id = rental.inventory_id 
GROUP BY inventory.film_id
)
SELECT rental_count_by_film.film_id, title
FROM film, rental_count_by_film
WHERE rental_count_by_film.count_film < 5
ORDER BY film_id;
