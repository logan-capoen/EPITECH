const express = require('express');
const router = express.Router();
const db = require('../config/db');
const path = require('path');
const bcrypt = require('bcryptjs');
const authenticateToken = require('../middleware/auth');

router.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '../public/users.html'));
});

router.get('/api', (req, res) => {
    const query = 'SELECT id, firstname, name, email FROM user';

    db.query(query, (error, results) => {
        if (error) {
            console.error('Error:', error);
            return res.status(500).json({ msg: 'An error occurred' });
        }
        res.json(results);
    });
});

router.get('/:id/page', (req, res) => {
    const id = req.params.id;

    if (id.includes('@'))
        res.sendFile(path.join(__dirname, '../public/users_mail.html'));
    else
        res.sendFile(path.join(__dirname, '../public/users_id.html'));
});

router.get('/:id', (req, res) => {
    const id = req.params.id;
    if (id.includes('@'))
        query = `SELECT id, email, password, name, firstname, DATE_FORMAT(created_at, '%Y-%m-%d %H:%i:%s') AS created_at FROM user WHERE email = ?`;
    else
        query = `SELECT id, email, password, name, firstname, DATE_FORMAT(created_at, '%Y-%m-%d %H:%i:%s') AS created_at FROM user WHERE id = ?`
    db.query(query, [id], (error, results) => {
        if (error) {
            console.error('Error:', error);
            return res.status(500).json({ msg: 'An error occurred' });
        }
        if (results.length === 0) {
            return res.status(404).json({ msg: 'Not found' });
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

router.put('/:id', async (req, res) => {
    const id = req.params.id;
    const { firstname, name, email, password } = req.body;

    const query = 'UPDATE user SET firstname = ?, name = ?, email = ?, password = ? WHERE id = ?';

    db.query(query, [firstname, name, email, await bcrypt.hash(req.body.password, 10), id], (error, results) => {
        if (error) {
            console.error('Error:', error);
            return res.status(500).json({ msg: 'An error occurred' });
        }
        if (results.affectedRows === 0) {
            return res.status(404).json({ msg: 'User not found' });
        }

        const selectQuery = `SELECT id, email, password, DATE_FORMAT(created_at, '%Y-%m-%d %H:%i:%s') AS created_at, firstname, name FROM user WHERE id = ?`;
            db.query(selectQuery, [id], (selectError, selectResults) => {
                if (selectError) {
                    console.error('Error:', selectError);
                    return res.status(500).json({ msg: 'An error occurred while retrieving updated user' });
                }
                if (selectResults.length === 0) {
                    return res.status(404).json({ msg: 'Not found' });
                }

                // Renvoie les informations mises à jour
                const updatedUser = selectResults[0];
                res.json({
                    id: updatedUser.id,
                    email: updatedUser.email,
                    password: updatedUser.password,
                    created_at: updatedUser.created_at,
                    firstname: updatedUser.firstname,
                    name: updatedUser.name,
                });
            });
    });
});

router.delete('/:id', (req, res) => {
    const id = req.params.id;

    const query = 'DELETE FROM user WHERE id = ?';

    db.query(query, [id], (error, results) => {
        if (error) {
            console.error('Error:', error);
            return res.status(500).json({ msg: 'An error occurred' });
        }
        if (results.affectedRows === 0) {
            return res.status(404).json({ msg: 'Not found' });
        }
        res.status(200).json({ msg: `Successfully deleted record number: ${id}` });
    });
});

module.exports = router;
