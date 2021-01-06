SELECT name FROM
people WHERE id IN (SELECT stars.person_id FROM stars JOIN movies ON stars.movie_id = movies.id
WHERE year = 2004 GROUP BY stars.person_id) ORDER BY birth;