import static org.junit.Assert.*;
import org.junit.*;
 
public class SolutionTest {
 
    private Solution s;
    private int k;
 
    /**
     * Sets up the test fixture. 
     * (Called before every test case method.)
     */
    @Before
    public void setUp() {
        s = new Solution();
    }
 
    /**
     * Tears down the test fixture. 
     * (Called after every test case method.)
     */
    @After
    public void tearDown() {
        s = null;
    }
    
    @Test
    public void test_1() {
        int[] nums = {3,0,1};
        assertEquals(2, s.missingNumber(nums));
    }
    
    @Test
    public void test_2() {
        int[] nums = {9,6,4,2,3,5,7,0,1};
        assertEquals(8, s.missingNumber(nums));
    }
}
