WITH rental_count_by_film AS 
(
SELECT film_id, COUNT(inventory.inventory_id) AS count_film
FROM inventory, rental
WHERE inventory.inventory_id = rental.inventory_id 
GROUP BY inventory.film_id
)
SELECT actor.actor_id, first_name, last_name
FROM film_actor, rental_count_by_film, actor
WHERE rental_count_by_film.count_film < 5
AND film_actor.film_id = rental_count_by_film.film_id 
AND film_actor.actor_id = actor.actor_id;
