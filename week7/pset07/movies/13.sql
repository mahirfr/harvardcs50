SELECT DISTINCT(name) FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id WHERE title IN (SELECT title FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id WHERE name ='Kevin Bacon' AND birth = 1958) AND name !='Kevin Bacon';

/* OR THIS SOLUTION:

SELECT DISTINCT(name) FROM people, movies, stars
   WHERE people.id = stars.person_id
        AND movies.id = stars.movie_id
        AND title IN
                (SELECT title FROM movies, people, stars
                WHERE people.id = stars.person_id
                    AND movies.id = stars.movie_id
                    AND name ='Kevin Bacon'
                    AND birth = 1958)
                    AND name != 'Kevin Bacon'; */