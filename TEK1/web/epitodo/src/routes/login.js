const express = require('express');
const router = express.Router();
const db = require('../config/db');
const path = require('path');
const bcrypt = require('bcryptjs');
const jwt = require("jsonwebtoken");

router.use(express.urlencoded({ extended: true }));
router.use(express.json());
router.use(express.static(path.join(__dirname, 'public')));

router.post('/', async (req, res) => {
    const { email, password } = req.body;

    try {
        const query = 'SELECT * FROM user WHERE email = ?';
        db.query(query, [email], async (error, results) => {
            if (error) {
                console.log('Error:', error);
                return res.status(500).json({ msg: 'An error occurred' });
            }
            if (results.length === 0)
                return res.status(401).json({ msg: 'Invalid Credentials' });
            const user = results[0];
            const isMatch = await bcrypt.compare(password, user.password);
            if (!isMatch)
                return res.status(401).json({ msg: 'Invalid Credentials' });
            const token = jwt.sign({ username: user.name, email: user.email }, process.env.SECRET, {});
            return res.status(200).json({token: token });
        });
    } catch (error) {
        console.log('Error:', error);
        res.status(500).json({ msg: 'An error occurred' });
    }
});

router.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '../public', 'login.html'));
})

module.exports = router;
