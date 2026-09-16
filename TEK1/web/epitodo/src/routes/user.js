const express = require("express");
const router = express.Router();
const db = require('../config/db');
const authenticateToken = require('../middleware/auth');

router.get('/', authenticateToken, (req, res) => {
    const userFromToken = req.user;

    const query = `SELECT id, email, password, name, firstname, DATE_FORMAT(created_at, '%Y-%m-%d %H:%i:%s') AS created_at FROM user WHERE email = ? AND name = ?`;
    db.query(query, [userFromToken.email, userFromToken.username], async (error, results) => {
        if (error) {
            return res.status(500).json({ msg: 'Internal server error' });
        }
        const user = results[0];
        res.json({
            id: user.id,
            email: user.email,
            password: user.password,
            created_at: user.created_at,
            firstname: user.firstname,
            name: user.name
        });
    });
});

router.get('/todos', authenticateToken, (req, res) => {
    const userFromToken = req.user;

    // Première requête : Récupère l'ID de l'utilisateur
    const query = 'SELECT id FROM user WHERE email = ? AND name = ?';
    db.query(query, [userFromToken.email, userFromToken.username], (error, results) => {
        if (error) {
            console.error('Error fetching user ID:', error);
            return res.status(500).json({ msg: 'Internal server error' });
        }

        if (results.length === 0) {
            return res.status(404).json({ msg: 'User not found' });
        }

        const user_id = results[0].id;

        // Deuxième requête : Récupère les tâches de l'utilisateur
        const query2 = `SELECT id, title, description, DATE_FORMAT(created_at, '%Y-%m-%d %H:%i:%s') AS created_at, DATE_FORMAT(due_time, '%Y-%m-%d %H:%i:%s') AS due_time, user_id, status FROM todo WHERE user_id = ?`;
        db.query(query2, [user_id], (error, results) => {
            if (error) {
                console.error('Error fetching todos:', error);
                return res.status(500).json({ msg: 'Internal server error' });
            }

            return res.status(200).json(results);
        });
    });
});
module.exports = router;
