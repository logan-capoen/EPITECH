const express = require('express');
const router = express.Router();
const db = require('../config/db');
const path = require('path');
const authenticateToken = require('../middleware/auth');

router.use(express.urlencoded({ extended: true }));
router.use(express.json());
router.use(express.static(path.join(__dirname, 'public')));

router.get('/page', async(req, res) => {
    res.sendFile(path.join(__dirname, '../public', 'todos.html'));
});

router.get('/', async (req, res) => {
    const query = `SELECT id, title, description, DATE_FORMAT(created_at, '%Y-%m-%d %H:%i:%s') AS created_at, DATE_FORMAT(due_time, '%Y-%m-%d %H:%i:%s') AS due_time, user_id, status FROM todo`;
    db.query(query, [], async(error, results) => {
        if (error) {
            return res.status(500).json({msg: 'Internal server error'});
        }
        return res.status(200).json(results);
    });
})

router.get('/:id', (req, res) => {
    const id = req.params.id;
    const query2 = `SELECT id, title, description, DATE_FORMAT(created_at, '%Y-%m-%d %H:%i:%s') AS created_at, DATE_FORMAT(due_time, '%Y-%m-%d %H:%i:%s') AS due_time, user_id, status FROM todo WHERE id = ?`;
    db.query(query2, [id], (error, results) => {
        if (error) {
            console.log('Error:', error);
            return res.status(500).json({ msg: 'Internal server error' });
        }
        if (results.length === 0) {
            return res.status(404).json({ msg: 'Not found' });
        }
        res.status(200).json(results[0]);
    });
})

router.post('/', (req, res) => {;
    const { title, description, due_time, user_id, status } = req.body;
    if (!title || !description || !due_time || !user_id)
        return res.status(400).json({ error: 'missing fields' });
    const query = 'INSERT INTO todo (title, description, due_time, user_id, status) VALUES (?, ?, ?, ?, ?)';
    db.query(query, [title, description, due_time, user_id, status], (error, results) => {
        if (error) {
            console.log('Error:', error);
            return res.status(500).json({ msg: 'Internal server error' });
        }
    });
    const query2 = `SELECT id, title, description, DATE_FORMAT(created_at, '%Y-%m-%d %H:%i:%s') AS created_at, DATE_FORMAT(due_time, '%Y-%m-%d %H:%i:%s') AS due_time, user_id, status FROM todo ORDER BY id DESC LIMIT 1`;
    db.query(query2, (error, results) => {
        if (error) {
            console.log('Error:', error);
            return res.status(500).json({ msg: 'Internal server error' });
        }
        res.status(201).json(results[0]);
    });
})

router.put('/:id', (req, res) => {
    const id = req.params.id;
    const { title, description, due_time, user_id, status } = req.body;
    if (!title || !description || !due_time || !user_id)
        return res.status(400).json({ error: 'missing fields' });
    const query = 'UPDATE todo SET title = ?, description = ?, due_time = ?, user_id = ?, status = ? WHERE id = ?';
    db.query(query, [title, description, due_time, user_id, status, id], (error, results) => {
        if (error) {
            console.log('Error:', error);
            return res.status(500).json({ msg: 'Internal server error' });
        }
    })
    const query2 = `SELECT id, title, description, DATE_FORMAT(created_at, '%Y-%m-%d %H:%i:%s') AS created_at, DATE_FORMAT(due_time, '%Y-%m-%d %H:%i:%s') AS due_time, user_id, status FROM todo WHERE id = ?`;;
    db.query(query2, [id], (error, results) => {
        if (error) {
            console.log('Error:', error);
            return res.status(500).json({ msg: 'Internal server error' });
        }
        if (results.length === 0) {
            return res.status(404).json({ msg: 'Not found' });
        }
        res.status(200).json(results[0]);
    });
})

router.delete('/:id', (req, res) => {
    const id = req.params.id;
    const query = 'DELETE FROM todo WHERE id = ?';
    db.query(query, [id], (error, results) => {
        if (error) {
            console.log('Error:', error);
            return res.status(500).json({ msg: 'Internal server error' });
        }
        if (results.affectedRows === 0) {
            return res.status(404).json({ msg: 'Not found' });
        }
        return res.status(200).json({ msg: `Successfully deleted record number : ${id}` });
    })
})

module.exports = router;
