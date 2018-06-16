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
        int[] nums = {};
        assertEquals(0, s.methodName(nums));
    }
}
